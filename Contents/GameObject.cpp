//*****************************************************************************
//* @file   GameObject.h
//* @brief  ゲームオブジェクトクラス
//* @note   ゲームで使用するオブジェクトクラス
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include "GameObject.h"
#include "Script.h"

void GAME_SYSTEMS::GameObject::SetUp()
{
	m_transform = AddComponent<Transform>();
	Setting();
}

void GAME_SYSTEMS::GameObject::ShutDown()
{
	for (auto& comp : m_componentList)
	{
		comp->Finalize();
	}
	m_componentList.clear();
}
