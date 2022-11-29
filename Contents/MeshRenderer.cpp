//*****************************************************************************
//* @file   MeshRenderer.cpp
//* @brief  
//* @note   ���b�V���̕`����s�����߂̃R���|�[�l���g
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

	// ���b�V�����擾
	for (uInt32 num = 0; num < m_mesh->GetMeshNum(); num++)
	{
		auto& meshData = m_mesh->GetMeshData(num);
		auto& vertexList = meshData->GetVertexData();
		auto& faceList = meshData->GetFaceData();

		// ���_��񐶐�
		Vector<MeshRenderer::Vertex> staticMeshVertexList;
		for (auto& vertex : vertexList)
		{
			MeshRenderer::Vertex addVertex;

			// ���_���W
			addVertex.Position = vertex->Position;

			// �J���[
			addVertex.Color.x = vertex->Color.r;
			addVertex.Color.y = vertex->Color.g;
			addVertex.Color.z = vertex->Color.b;
			addVertex.Color.w = vertex->Color.a;

			// �e�N�X�`��
			addVertex.Texcoord = vertex->Texcoord;

			// �@��
			addVertex.Normal = vertex->Normal;

			// �Z�b�g
			staticMeshVertexList.emplace_back(addVertex);
		}

		// �t�F�[�X��񐶐�
		Vector<uInt32> indicesList;
		for (auto& face : faceList)
		{
			for (auto i : face->Indices)
			{
				indicesList.emplace_back(i);			
			}
		}
		// �|���S������
		m_meshList.emplace_back(std::make_unique<RenderMesh>(staticMeshVertexList, indicesList));
	}
}


void GAME_SYSTEMS::MeshRenderer::Start()
{
	// �g�����X�t�H�[���擾
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("���b�V�������_���[ : ", GetOwner()->ToString());
		MessageWindow::Error("�g�����X�t�H�[�����R���|�[�l���g����Ă��܂���!");
	}

	// �}�e���A������
	if (m_material == nullptr)
	{
		m_material = std::make_shared<Material>();
		m_material->LoadShader(TEXT("DefaultMeshVertexShader"), TEXT("UnlitDefaultPixelShader"));
	}

	// ���b�V������
	CreateStaticMesh();
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	if (m_mesh == nullptr)
	{
		SYSTEMS::MessageWindow::GetInstance()->Error("Not Static Mesh");
		return;
	}

	// �萔�o�b�t�@�ݒ�
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// �V�F�[�_�[����
	m_material->SetShader();

	// �`��
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
