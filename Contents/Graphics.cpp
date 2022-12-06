//*****************************************************************************
//* @file   Graphics.cpp
//* @brief  
//* @note   グラフィック周りのコンポーネントの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Graphics.h"
#include "../System/GraphicsManager.h"
USING_GAME_SYSTEMS;

void GAME_SYSTEMS::Graphics::Initialize()
{
    GraphicsManager::GetInstance()->Register(this);
}

void GAME_SYSTEMS::Graphics::Finalize()
{
    GraphicsManager::GetInstance()->Remove(this);
}
