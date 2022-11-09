#include "ManagerInterface.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

#include "../DX11Settransform.h"
#include "../BoneTransform.h"
#include "../Skeleton.h"

USING_GAME_SYSTEMS;

void GAME_SYSTEMS::ManagerInterface::SetUp()
{
	ShaderManager::GetInstance()->SetUp();
	SceneManager::GetInstance()->Setup();
	DX11SetTransform::GetInstance()->Init();
	Skeleton::InitConstantBufferBoneMatrix(&systems::DirectXGraphics::GetInstance()->GetDevice());

}

void GAME_SYSTEMS::ManagerInterface::ShutDown()
{
	ShaderManager::GetInstance()->ShutDown();
	SceneManager::GetInstance()->Shutdown();
	Skeleton::UninitConstantBufferBoneMatrix();
	DX11SetTransform::GetInstance()->Uninit();

}
