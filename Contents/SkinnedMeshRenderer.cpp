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

#include "Material.h"
#include "Mesh.h"
#include "Skeleton.h"

#include "../Assimpscene.h"
#include "../Texture.h"
#include "../Animation.h"
#include "../AnimationClip.h"
#include "../BlendAnimation.h"


void GAME_SYSTEMS::SkinnedMeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("���b�V�������_���[ : ", GetOwner()->ToString());
		MessageWindow::Error("�g�����X�t�H�[�����R���|�[�l���g����Ă��܂���!");
	}

	// ���b�V���f�[�^����
	AssimpScene assimpScene;
	assimpScene.Init(TEXT("Assets/ThirdPerson.fbx"));
	m_meshData = std::make_shared<Mesh>();
	m_meshData->Load(&assimpScene);

	m_skelton = std::make_shared<Skeleton>();
	m_skelton->Load(&assimpScene);

	m_animation = std::make_shared<Animation>();
	m_animation->SetSkeleton(m_skelton.get());

	assimpScene.Exit();

#ifndef ANIM_BLEND
	// �A�j���[�V�����쐬
	assimpScene.Init(TEXT("Assets/ThirdPersonIdle.FBX"));
	m_animClip = std::make_unique<AnimationClip>();
	m_animClip->Load(&assimpScene, 0);
	assimpScene.Exit();
	m_animation->AddAnimationClips(m_animClip.get());
#else
	// �A�j���[�V�����ǉ�
	Array<T_String, 3> animationNameList;
	animationNameList[0] = TEXT("Assets/ThirdPersonIdle.FBX");
	animationNameList[1] = TEXT("Assets/ThirdPersonWalk.FBX");
	animationNameList[2] = TEXT("Assets/ThirdPersonRun.FBX");


	// �A�j���[�V�����N���b�v����
	for (int i = 0; i < animationNameList.size(); i++)
	{
		assimpScene.Init(animationNameList[i]);
		SharedPtr<AnimationClip> animPtr;
		animPtr = std::make_unique<AnimationClip>();
		animPtr->Load(&assimpScene, 0);
		m_animationClipList.emplace_back(std::move(animPtr));
		assimpScene.Exit();
	}

	// �u�����h�A�j���[�V�����쐬
	Float32 param = 0.0f;
	m_blendAnimation = std::make_shared<BlendAnimation>();
	for (auto& animClip : m_animationClipList)
	{
		m_blendAnimation->AddBlendSample(animClip.get(), param);
		param += 0.5f;
	}
	m_animation->AddAnimationClips(m_blendAnimation.get());

	// �A�j���[�V�����ǉ�
	for (auto& animClip : m_animationClipList)
	{
		m_animation->AddAnimationClips(animClip.get());
	}

#endif // !ANIM_BLEND

	// �}�e���A������
	// TODO : ���݂̓T���v���R�[�h�𒼐ڐ������邱�ƂŃ}�e���A�����쐬���Ă���
	m_material = std::make_shared<Material>();
	m_material->LoadShader(TEXT("vsoneskin"), TEXT("graymanps"));

	// �e�N�X�`������
	m_texture = std::make_shared<Texture>();
	m_texture->Load(TEXT("GraymanMaskTex.png"), "Assets");
}


void GAME_SYSTEMS::SkinnedMeshRenderer::Update()
{
	// �A�j���[�V�������X�V����
	m_animation->SetBlendParameter(m_blendParam);
	m_animation->UpdateAnimation(1.0f / 60.0f);
	m_animation->UpdateConstantBufferBoneMatrix();

	// �V�F�[�_�[����
	m_material->SetShader();
	// �e�N�X�`������
	m_texture->SetTexture(0);

	// ���[���h�s����R���X�^���g�o�b�t�@�ɐ�������
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// �`��
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	m_meshData->Draw(&deviceContext);
}
void GAME_SYSTEMS::SkinnedMeshRenderer::End()
{
	m_meshData->Unload();
	m_material->Unload();
	m_ownerTransform = nullptr;
}
