#include "ActionTestScene.h"
#include "SceneManager.h"
#include "Mouse.h"
#include "macro.h"

USING_GAME_SYSTEMS;

void ActionTestScene::ObjectEntry()
{
}

void ActionTestScene::BeginPlay()
{
	SetDisplayColor(255.0f, 0.0f, 0.0f);
}

void ActionTestScene::Tick()
{
	if (Mouse::Click(MouseCode::Left) == true)
	{
		SceneManager::GetInstance()->LoadScene("TestScene");
	}
}

void ActionTestScene::EndPlay()
{
}
