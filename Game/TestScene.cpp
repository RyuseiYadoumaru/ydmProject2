#include "TestScene.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "TestObject.h"
#include "CubeTest.h"
#include "DefaultCamera.h"
#include "MainCamera.h"
#include "GameContents.h"

#include "PlayerMovement.h"
#include "ThirdPersonCamera.h"

USING_GAME_SYSTEMS;

void TestScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<MainCamera>("Camera");
	m_test = GameObjectManager::GetInstance()->Instance<TestObject>("Player");
	m_obj = GameObjectManager::GetInstance()->Instance<CubeTest>("Cube");
	//GameObjectManager::GetInstance()->Instance<DefaultCamera>("Camera");
}

void TestScene::BeginPlay()
{
	SetDisplayColor(0.0f, 255.0f, 0.0f);
	//m_test->m_transform->m_rotation.y = 90.0f;
	m_obj->m_transform->m_scale.Set(5.0f, 5.0f, 5.0f);
	//m_obj->m_transform->m_rotation.Set(0.0f, 00.0f, 0.0f);
	//m_obj->m_transform->m_position.Set(0.0f, -10.0f, 0.0f);

}

void TestScene::Tick()
{
	//if (Keyboard::Trigger(Keycode::A) ||
	//	GamePad::Trigger(Xinput::A))
	//{
	//	SceneManager::GetInstance()->LoadScene("ActionTestScene");
	//}

}

void TestScene::EndPlay()
{
}

void TestScene::Render()
{
}

