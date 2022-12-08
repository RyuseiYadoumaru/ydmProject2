#include "Player.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"
USING_GAME_SYSTEMS;

void Player::Setting()
{
	// �����_�[�ݒ�
	auto meshRender = AddComponent<SkinnedMeshRenderer>();
	auto model = ResourceManager::GetInstance()->GetModelData("Basic_Motions_Dummy.FBX");
	meshRender->SetMesh(model->GetModel(0));
	meshRender->SetSkeleton(model->GetSkeleton());
	meshRender->GetMaterial()->AddTexture(ResourceManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);
	meshRender->GetMaterial()->SetPixelShader("GrayManps");

	// �A�j���[�V�����ݒ�
	auto anim = AddComponent<Animator>();

	// �n�ʈړ�
	auto blendAnim = anim->CreateBlendAnimation("MoveMent");
	auto animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_Idle01.fbx");
	blendAnim->AddBlendAnimation(animClip, 0.0f);
	animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_Walk01.fbx");
	blendAnim->AddBlendAnimation(animClip, 0.05f);
	animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_Run01.fbx");
	blendAnim->AddBlendAnimation(animClip, 0.7f);
	animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_Sprint01.fbx");
	blendAnim->AddBlendAnimation(animClip, 1.0f);
	
	// �󒆎�
	animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_AirMove.fbx");
	anim->AddAnimation("AirMove", animClip);

	// ���n
	animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_Landing02.fbx");
	anim->AddAnimation("LandGround", animClip);

	AddComponent<PlayerMovement>();
	auto playerOriginTrans = AddComponent<PlayerOriginTransform>();

	// ���W�ݒ�
	//m_transform->SetRotation(90.0f, 90.0f, 0.0f);
	playerOriginTrans->m_Rotation.Set(90.0f, 0.0f, 0.0f);
}
