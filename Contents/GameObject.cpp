//*****************************************************************************
//* @file   GameObject.h
//* @brief  �Q�[���I�u�W�F�N�g�N���X
//* @note   �Q�[���Ŏg�p����I�u�W�F�N�g�N���X
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
