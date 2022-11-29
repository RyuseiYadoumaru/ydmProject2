//*****************************************************************************
//* @file   MeshRenderer.cpp
//* @brief  
//* @note   メッシュの描画を行うためのコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "MeshRenderer.h"

#include "../System/MeshInfo.h"
#include "../System/MessageWindow.h"
#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "Debug.h"
#include "GameObject.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "../System/ThirdParty/Assimp/Assimpscene.h"

SharedPtr<Material> GAME_SYSTEMS::MeshRenderer::GetMaterial() noexcept
{
	if (m_material == nullptr)
	{
		m_material = std::make_shared<Material>();
		m_material->LoadShader(TEXT("DefaultMeshVertexShader"), TEXT("UnlitDefaultPixelShader"));
	}
	return m_material;
}

void GAME_SYSTEMS::MeshRenderer::CreateStaticMesh()
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
		Vector<MeshRenderer::Vertex> staticMeshVertexList;
		for (auto& vertex : vertexList)
		{
			MeshRenderer::Vertex addVertex;

			// 頂点座標
			addVertex.Position = vertex->Position;

			// カラー
			addVertex.Color.x = vertex->Color.r;
			addVertex.Color.y = vertex->Color.g;
			addVertex.Color.z = vertex->Color.b;
			addVertex.Color.w = vertex->Color.a;

			// テクスチャ
			addVertex.Texcoord = vertex->Texcoord;

			// 法線
			addVertex.Normal = vertex->Normal;

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


void GAME_SYSTEMS::MeshRenderer::Start()
{
	// トランスフォーム取得
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("メッシュレンダラー : ", GetOwner()->ToString());
		MessageWindow::Error("トランスフォームがコンポーネントされていません!");
	}

	// マテリアル生成
	if (m_material == nullptr)
	{
		m_material = std::make_shared<Material>();
		m_material->LoadShader(TEXT("DefaultMeshVertexShader"), TEXT("UnlitDefaultPixelShader"));
	}

	// メッシュ生成
	CreateStaticMesh();
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	if (m_mesh == nullptr)
	{
		SYSTEMS::MessageWindow::GetInstance()->Error("Not Static Mesh");
		return;
	}

	// 定数バッファ設定
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// シェーダー生成
	m_material->SetShader();

	// 描画
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	for (auto& mesh : m_meshList)
	{
		mesh->Draw(&deviceContext);
	}
}

void GAME_SYSTEMS::MeshRenderer::End()
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
