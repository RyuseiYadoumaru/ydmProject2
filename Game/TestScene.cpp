#include "TestScene.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "TestObject.h"
#include "DefaultCamera.h"

USING_GAME_SYSTEMS;

void TestScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<DefaultCamera>("Camera");
	GameObjectManager::GetInstance()->Instance<TestObject>("testObject");
}

void TestScene::BeginPlay()
{
	SetDisplayColor(0.0f, 255.0f, 0.0f);
}

void TestScene::Tick()
{
	if (Keyboard::Trigger(Keycode::A) ||
		GamePad::Trigger(Xinput::A))
	{
		SceneManager::GetInstance()->LoadScene("ActionTestScene");
	}
}

void TestScene::EndPlay()
{
}

void TestScene::Render()
{
}

