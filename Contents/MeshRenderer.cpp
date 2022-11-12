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

#include "Material.h"
#include "Mesh.h"
#include "Skeleton.h"

#include "../Assimpscene.h"
#include "../Texture.h"
#include "../Animation.h"
#include "../AnimationClip.h"
#include "../BlendAnimation.h"

void GAME_SYSTEMS::MeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("���b�V�������_���[ : ", GetOwner()->ToString());
		MessageWindow::Error("�g�����X�t�H�[�����R���|�[�l���g����Ă��܂���!");
	}

	// ���b�V���f�[�^����
	m_meshData = std::make_shared<Mesh>();
	m_meshData->LoadCube();

	// �}�e���A������
	m_material = std::make_shared<Material>();
	if (m_useLit == true)
	{
		m_material->LoadShader(TEXT("vs"), TEXT("ps"));
	}
	else
	{
		m_material->LoadShader(TEXT("ShapeVertexShader"), TEXT("ShapePixelShader"));
	}
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	// �A�j���[�V�������X�V����
	//m_animation->SetBlendParameter(1.0f);

	//m_animation->UpdateAnimation(1.0f / 60.0f);
	//m_animation->UpdateConstantBufferBoneMatrix();

	// �萔�o�b�t�@�ݒ�
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// �V�F�[�_�[����
	m_material->SetShader();
	// �e�N�X�`������
	//m_texture->SetTexture(0);

	// �`��
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	m_meshData->Draw(&deviceContext);
}

void GAME_SYSTEMS::MeshRenderer::End()
{
	m_meshData->Unload();
	m_material->Unload();
	m_ownerTransform = nullptr;
}
