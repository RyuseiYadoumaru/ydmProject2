#include "Player.h"
#include "PlayerMovement.h"
USING_GAME_SYSTEMS;

void Player::Setting()
{
	// �����_���[�ݒ�
	auto meshRender = AddComponent<SkinnedMeshRenderer>();
	auto model = ResourceManager::GetInstance()->GetModelData("ThirdPerson.fbx");
	meshRender->SetMesh(model->GetModel(0));
	meshRender->SetSkeleton(model->GetSkeleton());
	meshRender->GetMaterial()->AddTexture(ResourceManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);
	meshRender->GetMaterial()->SetPixelShader("GrayManps");

	// �A�j���[�V�����ݒ�
	auto anim = AddComponent<Animator>();
	auto blendAnim = anim->CreateBlendAnimation("MoveMent");
	auto animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonIdle.FBX");
	blendAnim->AddBlendAnimation(animClip, 0.0f);
	animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonWalk.FBX");
	blendAnim->AddBlendAnimation(animClip, 0.5f);
	animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonRun.fbx");
	blendAnim->AddBlendAnimation(animClip, 1.0f);

	AddComponent<PlayerMovement>();

	// ���W�ݒ�
	m_transform->m_rotation.Set(90.0f, 0.0f, 0.0f);
}
