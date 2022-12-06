//*****************************************************************************
//* @file   Miscellaneous.cpp
//* @brief  
//* @note   雑多なコンポーネントの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Miscellaneous.h"
#include "../System/MiscellaneousManager.h"

void GAME_SYSTEMS::Miscellaneous::Initialize()
{
    MiscellaneousManager::GetInstance()->Register(this);
}

void GAME_SYSTEMS::Miscellaneous::Finalize()
{
    MiscellaneousManager::GetInstance()->Remove(this);
}
