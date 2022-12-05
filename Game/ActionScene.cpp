#include "GameContents.h"
#include "ActionScene.h"
#include "DebugCamera.h"
#include "PlayerTrackingCamera.h"
#include "MainCamera.h"
#include "Player.h"

#include "CubeTest.h"


void ActionScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<PlayerTrackingCamera>("Camera");
	GameObjectManager::GetInstance()->Instance<DebugCamera>("Camera");
	GameObjectManager::GetInstance()->Instance<Player>("Player");
	GameObjectManager::GetInstance()->Instance<CubeTest>("Cube");
}

void ActionScene::BeginPlay()
{
	SetDisplayColor(0.0f, 0.0f, 0.0f);
	m_player = GameObjectManager::GetInstance()->Find("Player");
	m_test = GameObjectManager::GetInstance()->Find("Cube");
	m_frameCounter = 0;
}

void ActionScene::Tick()
{
	Float32 s = 10.0f;
	printf("\n\n%d", m_frameCounter);
	m_frameCounter++;
	if (Keyboard::Press(Keycode::RightArrow))
	{
		m_player->m_transform->m_rotation.y += s;
		//m_test->m_transform->m_rotation.y += s;
	}
	else if (Keyboard::Press(Keycode::LeftArrow))
	{
		m_player->m_transform->m_rotation.y -= s;
		//m_test->m_transform->m_rotation.y -= s;
	}
	if (Keyboard::Press(Keycode::F1))
	{
		m_player->m_transform->m_scale.x += 0.05f;
		m_player->m_transform->m_scale.y += 0.05f;
		m_player->m_transform->m_scale.z += 0.05f;
		//m_test->m_transform->m_rotation.z += s;
	}
	else if (Keyboard::Press(Keycode::F2))
	{
		m_player->m_transform->m_scale.x -= 0.05f;
		m_player->m_transform->m_scale.y -= 0.05f;
		m_player->m_transform->m_scale.z -= 0.05f;
		//m_test->m_transform->m_rotation.z -= s;
	}

	if (Keyboard::Press(Keycode::A))
	{
		m_player->m_transform->m_rotation.x += s;
		//m_test->m_transform->m_rotation.x += s;
	}
	else if (Keyboard::Press(Keycode::D))
	{
		m_player->m_transform->m_rotation.x -= s;
		//m_test->m_transform->m_rotation.x -= s;
	}



}

void ActionScene::EndPlay()
{
}
