#include "TestObject.h"
#include "TestScript.h"
#include "../Game/PlayerMovement.h"
#include "GameContents.h"


USING_GAME_SYSTEMS;

void TestObject::Setting()
{

	auto meshRender = AddComponent<SkinnedMeshRenderer>();
	auto model = ResourceManager::GetInstance()->GetModelData("ThirdPerson.fbx");
	meshRender->SetMesh(model->GetModel(0));
	meshRender->SetSkeleton(model->GetSkeleton());
	meshRender->GetMaterial()->AddTexture(ResourceManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);
	meshRender->GetMaterial()->SetPixelShader("GrayManps");

	// アニメーション設定
	auto anim = AddComponent<Animator>();
	auto blendAnim = anim->CreateBlendAnimation("MoveMent");
	auto animClip =ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonIdle.FBX");
	blendAnim->AddBlendAnimation(animClip, 0.0f);
	animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonWalk.FBX");
	blendAnim->AddBlendAnimation(animClip, 0.5f);
	animClip = ResourceManager::GetInstance()->GetAnimationClip("ThirdPersonRun.fbx");
	blendAnim->AddBlendAnimation(animClip, 1.0f);

	AddComponent<PlayerMovement>();
	//auto skinned = AddComponent<SkinnedMeshRenderer>();
	//skinned->SetMesh(ResourceManager::GetInstance()->GetSkeletalMesh("ThirdPerson.fbx"));
	//skinned->GetMaterial()->SetPixelShader("GrayManps");
	//skinned->GetMaterial()->AddTexture(TextureManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);

	//skinned->GetMesh()->AddAnimationClip(TEXT("Assets/ThirdPersonWalk.FBX"));
	//skinned->GetMesh()->AddAnimationClip(TEXT("Assets/ThirdPersonRun.FBX"));


	//// ブレンドアニメーション
	//auto blendMove = anim->CreateBlendAnimation("MoveMent");
	//blendMove->AddBlendAnimation(skinned->GetMesh()->GetAnimationClip(), 0.0f);
	//blendMove->AddBlendAnimation(skinned->GetMesh()->GetAnimationClip("ThirdPersonWalk.FBX"), 0.5f);
	//blendMove->AddBlendAnimation(skinned->GetMesh()->GetAnimationClip("ThirdPersonRun.FBX"), 1.0f);

}
