#include "GameContents.h"
#include "ActionScene.h"
#include "MainCamera.h"
#include "Player.h"

#include "CubeTest.h"


void ActionScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<MainCamera>("Camera");
	GameObjectManager::GetInstance()->Instance<Player>("Player");
	GameObjectManager::GetInstance()->Instance<CubeTest>("Cube");
}

void ActionScene::BeginPlay()
{
	m_player = GameObjectManager::GetInstance()->Find("Player");
}

void ActionScene::Tick()
{
}

void ActionScene::EndPlay()
{
}
