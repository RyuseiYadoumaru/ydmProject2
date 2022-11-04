#include "TestScene.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "Keyboard.h"
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
	if (Keyboard::Trigger(Keycode::A))
	{
		SceneManager::GetInstance()->LoadScene("ActionTestScene");
	}
}

void TestScene::EndPlay()
{
}
