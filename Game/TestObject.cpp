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
}
