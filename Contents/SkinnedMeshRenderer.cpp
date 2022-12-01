//*****************************************************************************
//* @file   SkinnedMeshRenderer.cpp
//* @brief  
//* @note   ボーンアニメーションつきのメッシュを描画を行うコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "SkinnedMeshRenderer.h"

#include "../System/MeshInfo.h"
#include "../System/MessageWindow.h"
#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "../System/DX11SetBoneMatrix.h"
#include "Debug.h"
#include "GameObject.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Skeleton.h"
#include "Model.h"

#include "../System/ThirdParty/Assimp/Assimpscene.h"
//#include "../Animation.h"
//#include "../AnimationClip.h"


SharedPtr<Material> GAME_SYSTEMS::SkinnedMeshRenderer::GetMaterial() noexcept
{
	if (m_material == nullptr)
	{
		m_material = std::make_shared<Material>();
		m_material->LoadShader(TEXT("SkinnedVertexShader"), TEXT("UnlitDefaultPixelShader"));
	}
	return m_material;
}

void GAME_SYSTEMS::SkinnedMeshRenderer::CreateSkeletonMesh()
{
	if (m_meshList.empty() == false)
	{
		for (auto& mesh : m_meshList)
		{
			mesh->Uninit();
		}
		m_meshList.clear();
	}

	// メッシュ情報取得
	for (uInt32 num = 0; num < m_mesh->GetMeshNum(); num++)
	{
		auto& meshData = m_mesh->GetMeshData(num);
		auto& vertexList = meshData->GetVertexData();
		auto& faceList = meshData->GetFaceData();

		// 頂点情報生成
		Vector<SkinnedMeshRenderer::Vertex> staticMeshVertexList;
		for (auto& vertex : vertexList)
		{
			SkinnedMeshRenderer::Vertex addVertex;

			// 頂点座標
			addVertex.Position = vertex->Position;

			// テクスチャ
			addVertex.Texcoord = vertex->Texcoord;

			// 法線
			addVertex.Normal = vertex->Normal;

			// ボーン情報			
			addVertex.BoneIndex[0] = vertex->BoneIndex[0];
			addVertex.BoneIndex[1] = vertex->BoneIndex[1];
			addVertex.BoneIndex[2] = vertex->BoneIndex[2];
			addVertex.BoneIndex[3] = vertex->BoneIndex[3];

			addVertex.BoneWeight[0] = vertex->BoneWeight[0];
			addVertex.BoneWeight[1] = vertex->BoneWeight[1];
			addVertex.BoneWeight[2] = vertex->BoneWeight[2];
			addVertex.BoneWeight[3] = vertex->BoneWeight[3];

			addVertex.BoneNum = vertex->BoneNum;

			// セット
			staticMeshVertexList.emplace_back(addVertex);
		}

		// フェース情報生成
		Vector<uInt32> indicesList;
		for (auto& face : faceList)
		{
			for (auto i : face->Indices)
			{
				indicesList.emplace_back(i);
			}
		}
		// ポリゴン生成
		m_meshList.emplace_back(std::make_unique<RenderMesh>(staticMeshVertexList, indicesList));
	}

}


void GAME_SYSTEMS::SkinnedMeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("メッシュレンダラー : ", GetOwner()->ToString());
		MessageWindow::Error("トランスフォームがコンポーネントされていません!");
	}

	if (m_material == nullptr)
	{
		m_material = std::make_shared<Material>();
		m_material->LoadShader(TEXT("SkinnedVertexShader"), TEXT("UnlitDefaultPixelShader"));
	}

	// メッシュ生成
	CreateSkeletonMesh();
}

void GAME_SYSTEMS::SkinnedMeshRenderer::Update()
{
	if (m_mesh == nullptr)
	{
		SYSTEMS::MessageWindow::GetInstance()->Error("Not Skinned Mesh");
		return;
	}

	// シェーダー生成
	m_material->SetShader();

	// ワールド行列をコンスタントバッファに生成する
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);
	// ボーン行列生成
	Vector<DirectX::XMFLOAT4X4> skeletonMatrixList;
	for (auto& mtx : m_skeleton->GetBonesMatrix())
	{
		skeletonMatrixList.emplace_back(mtx);
	}
	systems::DX11SetBoneMatrix::GetInstance()->SetConstantBuffer(skeletonMatrixList);

	// 描画
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	for (auto& mesh : m_meshList)
	{
		mesh->Draw(&deviceContext);
	}
}
void GAME_SYSTEMS::SkinnedMeshRenderer::End()
{
	m_mesh = nullptr;
	m_material = nullptr;
	m_ownerTransform = nullptr;
	for (auto& mesh : m_meshList)
	{
		mesh->Uninit();
	}
	m_meshList.clear();
}
