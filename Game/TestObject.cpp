#include "TestObject.h"
#include "TestScript.h"
#include "../Game/PlayerMovement.h"
#include "GameContents.h"


USING_GAME_SYSTEMS;

void TestObject::Setting()
{
	AddComponent<TestScript>();
	auto skinned = AddComponent<SkinnedMeshRenderer>();
	AddComponent<PlayerMovement>();
	skinned->SetMesh(MeshManager::GetInstance()->GetSkeletalMesh("ThirdPerson.fbx"));
	skinned->GetMaterial()->SetPixelShader("GrayManps");
	skinned->GetMaterial()->AddTexture(TextureManager::GetInstance()->GetTexture("GraymanMaskTex.png"), 0);

	//skinned->GetMesh()->AddAnimationClip(TEXT("Assets/ThirdPersonWalk.FBX"));
	//skinned->GetMesh()->AddAnimationClip(TEXT("Assets/ThirdPersonRun.FBX"));

	//// アニメーション設定
	//auto anim = AddComponent<Animator>();
	//anim->AddAnimation("Idle", skinned->GetMesh()->GetAnimationClip());

	//// ブレンドアニメーション
	//auto blendMove = anim->CreateBlendAnimation("MoveMent");
	//blendMove->AddBlendAnimation(skinned->GetMesh()->GetAnimationClip(), 0.0f);
	//blendMove->AddBlendAnimation(skinned->GetMesh()->GetAnimationClip("ThirdPersonWalk.FBX"), 0.5f);
	//blendMove->AddBlendAnimation(skinned->GetMesh()->GetAnimationClip("ThirdPersonRun.FBX"), 1.0f);

}
