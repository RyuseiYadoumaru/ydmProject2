//*****************************************************************************
//* @file   Graphics.cpp
//* @brief  
//* @note   �O���t�B�b�N����̃R���|�[�l���g�̊��N���X
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
