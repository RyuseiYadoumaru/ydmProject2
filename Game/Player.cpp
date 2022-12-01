#include "Player.h"
#include "PlayerMovement.h"
USING_GAME_SYSTEMS;

void Player::Setting()
{
	// レンダラー設定
	//auto meshRender = AddComponent<SkinnedMeshRenderer>();
	//auto model = ResourceManager::GetInstance()->GetModelData("ThirdPerson.fbx");
	//meshRender->SetMesh(model->GetModel(0));
	//meshRender->SetSkeleton(model->GetSkeleton());
	//meshRender->GetMaterial()->AddTexture(ResourceManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);
	//meshRender->GetMaterial()->SetPixelShader("GrayManps");

	//// アニメーション設定
	//auto anim = AddComponent<Animator>();
	//auto blendAnim = anim->CreateBlendAnimation("MoveMent");
	//auto animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonIdle.FBX");
	//blendAnim->AddBlendAnimation(animClip, 0.0f);
	//animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonWalk.FBX");
	//blendAnim->AddBlendAnimation(animClip, 0.5f);
	//animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonRun.fbx");
	//blendAnim->AddBlendAnimation(animClip, 1.0f);

	//AddComponent<PlayerMovement>();

	//// 座標設定
	//m_transform->m_rotation.Set(90.0f, 0.0f, 0.0f);


	//auto meshRender = AddComponent<MeshRenderer>();
	//auto model = ResourceManager::GetInstance()->GetModelData("Basic_Motions_Dummy.FBX");
	//meshRender->SetMesh(model->GetModel(0));
	//meshRender->GetMaterial()->AddTexture(ResourceManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);
	//meshRender->GetMaterial()->SetPixelShader("GrayManps");
	//// 座標設定
	//m_transform->m_rotation.Set(180.0f, 0.0f, 0.0f);


	auto meshRender = AddComponent<SkinnedMeshRenderer>();
	auto model = ResourceManager::GetInstance()->GetModelData("Basic_Motions_Dummy.FBX");
	meshRender->SetMesh(model->GetModel(0));
	meshRender->SetSkeleton(model->GetSkeleton());
	meshRender->GetMaterial()->AddTexture(ResourceManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);
	meshRender->GetMaterial()->SetPixelShader("GrayManps");

	// アニメーション設定
	auto anim = AddComponent<Animator>();
	//auto blendAnim = anim->CreateBlendAnimation("MoveMent");
	auto animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_Idle01.fbx");
	anim->AddAnimation("Walk", animClip);
	//blendAnim->AddBlendAnimation(animClip, 0.0f);
	//animClip = ResourceManager::GetInstance()->GetAnimationClip("BasicMotions_Walk01.fbx");
	//blendAnim->AddBlendAnimation(animClip, 1.0f);

	//AddComponent<PlayerMovement>();
	anim->Play("Walk");

	// 座標設定
	m_transform->m_rotation.Set(90.0f, 0.0f, 0.0f);

}
