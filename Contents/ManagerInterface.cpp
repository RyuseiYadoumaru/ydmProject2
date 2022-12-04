#include "ManagerInterface.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "DeveloperMenu.h"

#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "../System/DX11SetBoneMatrix.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;

void GAME_SYSTEMS::ManagerInterface::SetUp()
{
	ShaderManager::GetInstance()->SetUp();
	SceneManager::GetInstance()->Setup();
	ResourceManager::GetInstance()->SetUp();
	DX11SetTransform::GetInstance()->Init();
	DX11SetMaterial::GetInstance()->Initialize();
	DX11SetBoneMatrix::GetInstance()->Initialize();
	developer::DeveloperMenu::SetUp();
}

void GAME_SYSTEMS::ManagerInterface::ShutDown()
{
	developer::DeveloperMenu::ShutDown();
	ResourceManager::GetInstance()->ShutDown();
	ShaderManager::GetInstance()->ShutDown();
	SceneManager::GetInstance()->Shutdown();
	DX11SetBoneMatrix::GetInstance()->Finalize();
	DX11SetMaterial::GetInstance()->Finalize();
	DX11SetTransform::GetInstance()->Uninit();
}
