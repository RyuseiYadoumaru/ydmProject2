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
	m_frameCounter = 0;
}

void ActionScene::Tick()
{
	printf("\n\n%d", m_frameCounter);
	m_frameCounter++;
	if (Keyboard::Press(Keycode::UpArrow))
	{
		m_player->m_transform->m_rotation.x += 5.0f;
	}
	if (Keyboard::Press(Keycode::RightArrow))
	{
		m_player->m_transform->m_rotation.y += 5.0f;
	}
}

void ActionScene::EndPlay()
{
}
