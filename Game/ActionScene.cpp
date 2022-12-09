#include "GameContents.h"
#include "ActionScene.h"
#include "DebugCamera.h"
#include "PlayerTrackingCamera.h"
#include "MainCamera.h"
#include "Player.h"
#include "Item.h"
#include "HitObjectManager.h"

#include "CubeTest.h"


void ActionScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<PlayerTrackingCamera>("Camera");
	GameObjectManager::GetInstance()->Instance<DebugCamera>("DebugCamera");
	GameObjectManager::GetInstance()->Instance<Player>("Player");
	GameObjectManager::GetInstance()->Instance<CubeTest>("Cube");
	
	GameObjectManager::GetInstance()->Instance<Item>("Item");
	GameObjectManager::GetInstance()->Instance<Item>("Item");
	GameObjectManager::GetInstance()->Instance<Item>("Item");
	GameObjectManager::GetInstance()->Instance<Item>("Item");
	GameObjectManager::GetInstance()->Instance<Item>("Item");
	GameObjectManager::GetInstance()->Instance<Item>("Item");
	GameObjectManager::GetInstance()->Instance<Item>("Item");

	GameObjectManager::GetInstance()->Instance<HitObjectManager>("HitObjectManager");
}

void ActionScene::BeginPlay()
{
	SetDisplayColor(0.0f, 0.0f, 0.0f);
	m_player = GameObjectManager::GetInstance()->Find("Player");
	m_test = GameObjectManager::GetInstance()->Find("Cube");
	//m_test->m_transform->m_Position.x += 300.0f;
	//m_test->m_transform->m_Position.z += 300.0f;
	m_frameCounter = 0;
}

void ActionScene::Tick()
{
	printf("\n\n%d", m_frameCounter);
	m_frameCounter++;
	//DebugTick();
}

void ActionScene::EndPlay()
{
}

void ActionScene::DebugTick()
{
	Float32 s = 10.0f;
	auto rot = m_player->m_transform->GetEulerAngles();
	printf("\nX:%f, Y:%f, Z:%f", rot.x, rot.y, rot.z);
	if (Keyboard::Press(Keycode::RightArrow))
	{
		rot.y += s;
		//m_test->m_transform->m_rotation.y += s;
	}
	else if (Keyboard::Press(Keycode::LeftArrow))
	{
		rot.y -= s;
		//m_test->m_transform->m_rotation.y -= s;
	}
	if (Keyboard::Press(Keycode::F1))
	{
		m_player->m_transform->m_Scale.x += 0.05f;
		m_player->m_transform->m_Scale.y += 0.05f;
		m_player->m_transform->m_Scale.z += 0.05f;
		//m_test->m_transform->m_rotation.z += s;
	}
	else if (Keyboard::Press(Keycode::F2))
	{
		m_player->m_transform->m_Scale.x -= 0.05f;
		m_player->m_transform->m_Scale.y -= 0.05f;
		m_player->m_transform->m_Scale.z -= 0.05f;
		//m_test->m_transform->m_rotation.z -= s;
	}

	if (Keyboard::Press(Keycode::A))
	{
		rot.x += s;
		//m_test->m_transform->m_rotation.x += s;
	}
	else if (Keyboard::Press(Keycode::D))
	{
		rot.x -= s;
		//m_test->m_transform->m_rotation.x -= s;
	}
	if (Keyboard::Press(Keycode::F3))
	{
		rot.z += s;
		//m_test->m_transform->m_rotation.x += s;
	}
	else if (Keyboard::Press(Keycode::F4))
	{
		rot.z -= s;
		//m_test->m_transform->m_rotation.x -= s;
	}

	// ‰ñ“]
	//m_player->m_transform->SetRotation(rot.x, rot.y, rot.z);
}
