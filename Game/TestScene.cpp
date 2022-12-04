#include "TestScene.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "TestObject.h"
#include "CubeTest.h"
#include "DefaultCamera.h"
#include "MainCamera.h"
#include "SphareTest.h"
#include "GameContents.h"

#include "EnemyGenerator.h"
#include "PlayerMovement.h"
#include "ThirdPersonCamera.h"

USING_GAME_SYSTEMS;

void TestScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<MainCamera>("Camera");
	m_obj = GameObjectManager::GetInstance()->Instance<CubeTest>("Cube");	
}

void TestScene::BeginPlay()
{
	SetDisplayColor(0.0f, 1.0f, 0.0f);
}

void TestScene::Tick()
{
}

void TestScene::EndPlay()
{
}

