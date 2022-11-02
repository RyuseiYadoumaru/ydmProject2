//*****************************************************************************
//* @file   GameSystem.cpp
//* @brief  ゲームシステムクラス
//* @note   ゲームシステムに必要なサブシステム管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include "GameSystem.h"
#include "GameSystemManager.h"
#include "Framelate.h"
#include "Debug.h"
//#include "../../Subsystems/Subsystem.h"
//#include "../../Subsystems/GameSubSysmte.h"
//#include "../../Subsystems/Manager.h"
//#include "../Systems/Subsystems/GameSubSystemInstance.h"
//#include "../Contents/Manager/ManagerInstance.h"
//#include "../Message/MessageWindow.h"
//#include "Config.h"

USING_GAME_SYSTEMS
/**============================================================================
//! @func   SetUp
//! @brief  初期化
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::SetUp()
{
    GameSystemManager::GetInstance()->Create<Framelate>("Framelate", gameUpdate::Type::Last, 255, true);

    return true;
}


/**============================================================================
//! @func   ShutDown
//! @brief  終了処理
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::ShutDown()
{
    return true;
}


/**============================================================================
//! @func   Initialaze
//! @brief  ゲームサブシステムの初期化
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::Initialaze()
{
    auto gameSystem = GameSystemManager::GetInstance();
    // サブシステムの更新順番で初期化が行われる
    for (auto& stage : gameSystem->m_gameSubSystemList)
    {
        for (auto& subSystemList : stage.second)
        {
            for (auto& system : subSystemList.second)
            {
                system.second->Initialize();
            }
        }
    }

    return true;
}


/**============================================================================
//! @func   Run
//! @brief  ゲームの更新
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::Run()
{
    auto gameSystem = GameSystemManager::GetInstance();
    for (auto& stage : gameSystem->m_gameSubSystemList)
    {
        if (stage.first == gameUpdate::Type::None || stage.second.empty() == true) break;
        for (auto& subSystemList : stage.second)
        {
            for (auto& system : subSystemList.second)
            {
                system.second->Run();
            }
        }
    }
    return true;
}


/**============================================================================
//! @func   Finalize
//! @brief  ゲーム終了処理
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::Finalize()
{
    gameSystems::GameSystemManager::GetInstance()->Releace();
    return true;
}