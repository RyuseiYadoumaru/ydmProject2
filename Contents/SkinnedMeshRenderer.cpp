//*****************************************************************************
//* @file   SkinnedMeshRenderer.cpp
//* @brief  
//* @note   �{�[���A�j���[�V�������̃��b�V����`����s���R���|�[�l���g
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "SkinnedMeshRenderer.h"

#include "../System/MessageWindow.h"
#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "../System/DX11SetBoneMatrix.h"
#include "Debug.h"
#include "GameObject.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#define ANIM_BLEND

#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Skeleton.h"

#include "TextureManager.h"

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

SharedPtr<Skeleton> GAME_SYSTEMS::SkinnedMeshRenderer::GetSkeleton() noexcept
{
	return m_mesh->GetSkeleton();
}

void GAME_SYSTEMS::SkinnedMeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("���b�V�������_���[ : ", GetOwner()->ToString());
		MessageWindow::Error("�g�����X�t�H�[�����R���|�[�l���g����Ă��܂���!");
	}

	if (m_material == nullptr)
	{
		m_material = std::make_shared<Material>();
		m_material->LoadShader(TEXT("SkinnedVertexShader"), TEXT("UnlitDefaultPixelShader"));
	}

}

void GAME_SYSTEMS::SkinnedMeshRenderer::Update()
{
	if (m_mesh == nullptr)
	{
		SYSTEMS::MessageWindow::GetInstance()->Error("Not Skinned Mesh");
		return;
	}

	// �V�F�[�_�[����
	m_material->SetShader();

	// ���[���h�s����R���X�^���g�o�b�t�@�ɐ�������
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// �`��
	m_mesh->Render();
}
void GAME_SYSTEMS::SkinnedMeshRenderer::End()
{
	m_mesh->Releace();
	m_material->Unload();
	m_ownerTransform = nullptr;
}
