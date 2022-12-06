//*****************************************************************************
//* @file   Physics.cpp
//* @brief  
//* @note   �����n�̃R���|�[�l���g�̊��N���X
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Physics.h"
#include "../System/PhysicsManager.h"

USING_GAME_SYSTEMS;

void GAME_SYSTEMS::Physics::Initialize()
{
    PhysicsManager::GetInstance()->Register(this);
}

void GAME_SYSTEMS::Physics::Finalize()
{
    PhysicsManager::GetInstance()->Remove(this);
}
