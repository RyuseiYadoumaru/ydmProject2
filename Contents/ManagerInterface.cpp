#include "ManagerInterface.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "MeshManager.h"
#include "GameObjectManager.h"

#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "../System/DX11SetBoneMatrix.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;

void GAME_SYSTEMS::ManagerInterface::SetUp()
{
	ShaderManager::GetInstance()->SetUp();
	SceneManager::GetInstance()->Setup();
	MeshManager::GetInstance()->SetUp();
	DX11SetTransform::GetInstance()->Init();
	DX11SetMaterial::GetInstance()->Initialize();
	DX11SetBoneMatrix::GetInstance()->Initialize();

}

void GAME_SYSTEMS::ManagerInterface::ShutDown()
{
	MeshManager::GetInstance()->ShutDown();
	ShaderManager::GetInstance()->ShutDown();
	SceneManager::GetInstance()->Shutdown();
	DX11SetBoneMatrix::GetInstance()->Finalize();
	DX11SetMaterial::GetInstance()->Finalize();
	DX11SetTransform::GetInstance()->Uninit();
}
