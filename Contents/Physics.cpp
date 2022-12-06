//*****************************************************************************
//* @file   Physics.cpp
//* @brief  
//* @note   物理系のコンポーネントの基底クラス
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
