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

void GAME_SYSTEMS::GameObject::ShutDown()
{
	m_componentList.clear();
}

void GAME_SYSTEMS::GameObject::ComponentStart()
{
	for (auto& comp : m_componentList)
	{
		comp->Start();
	}
}

void GAME_SYSTEMS::GameObject::ComponentEnd()
{
	for (auto& comp : m_componentList)
	{
		comp->End();
		comp->Finalize();
	}
}
