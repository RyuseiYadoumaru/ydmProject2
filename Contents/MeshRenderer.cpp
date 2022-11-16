//*****************************************************************************
//* @file   MeshRenderer.cpp
//* @brief  
//* @note   ���b�V���̕`����s�����߂̃R���|�[�l���g
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "MeshRenderer.h"

#include "../System/MessageWindow.h"
#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "Debug.h"
#include "GameObject.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#include "StaticMesh.h"
#include "Material.h"
#include "../System/ThirdParty/Assimp/Assimpscene.h"
#include "../Texture.h"


void GAME_SYSTEMS::MeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("���b�V�������_���[ : ", GetOwner()->ToString());
		MessageWindow::Error("�g�����X�t�H�[�����R���|�[�l���g����Ă��܂���!");
	}

	// �}�e���A������
	m_material = m_meshData->GetMaterial();

	// �e�N�X�`������
	m_texture = std::make_shared<Texture>();
	m_texture->Load(TEXT("MeshTexture.png"), TEXT("Assets"));
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	// �萔�o�b�t�@�ݒ�
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// �V�F�[�_�[����
	m_material->SetShader();
	// �e�N�X�`������
	m_texture->SetTexture(0);

	// �`��
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	m_meshData->Render();
}

void GAME_SYSTEMS::MeshRenderer::End()
{
	//m_meshData->Releace();
	//m_meshData->Unload();
	//m_material->Unload();
	m_ownerTransform = nullptr;
}
