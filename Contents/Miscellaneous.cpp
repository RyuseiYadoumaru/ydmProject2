//*****************************************************************************
//* @file   Miscellaneous.cpp
//* @brief  
//* @note   雑多なコンポーネントの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Miscellaneous.h"

Map<GAME_SYSTEMS::Miscellaneous::Type, Unordered_Map<uInt32, GAME_SYSTEMS::Miscellaneous*>> GAME_SYSTEMS::Miscellaneous::m_miscellaneousList;

bool GAME_SYSTEMS::Miscellaneous::MiscellaneousUpdate()
{
    for (auto& miscellaneousStage : m_miscellaneousList)
    {
        for (auto& miscellaneous : miscellaneousStage.second)
        {
            miscellaneous.second->Update();
        }
    }    return true;
}

bool GAME_SYSTEMS::Miscellaneous::MiscellaneousReleace()
{
    m_miscellaneousList.clear();
    return true;
}

void GAME_SYSTEMS::Miscellaneous::Initialize()
{
    m_miscellaneousList[m_type][m_id] = this;
}

void GAME_SYSTEMS::Miscellaneous::Finalize()
{
    m_miscellaneousList[m_type].erase(m_id);
}
