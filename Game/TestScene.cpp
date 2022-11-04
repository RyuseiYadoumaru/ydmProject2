#include "TestScene.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "TestObject.h"

USING_GAME_SYSTEMS;

void TestScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<TestObject>("testObject");
}

void TestScene::BeginPlay()
{
	SetDisplayColor(0.0f, 255.0f, 0.0f);
}

void TestScene::Tick()
{
}

void TestScene::EndPlay()
{
}
