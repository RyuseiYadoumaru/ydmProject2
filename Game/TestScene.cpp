#include "TestScene.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "TestObject.h"
#include "DefaultCamera.h"
#include "MainCamera.h"
#include "GameContents.h"

#include "PlayerMovement.h"
#include "ThirdPersonCamera.h"

USING_GAME_SYSTEMS;

void TestScene::ObjectEntry()
{
	m_test = GameObjectManager::GetInstance()->Instance<TestObject>("Player");
	GameObjectManager::GetInstance()->Instance<MainCamera>("Camera");
}

void TestScene::BeginPlay()
{
	SetDisplayColor(0.0f, 255.0f, 0.0f);
	m_test->m_transform->m_rotation.y = 90.0f;
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

