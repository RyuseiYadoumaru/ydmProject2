//*****************************************************************************
//* @file   GameSystem.cpp
//* @brief  ゲームシステムクラス
//* @note   ゲームシステムに必要なサブシステム管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include "GameSystem.h"
#include "GameSubSystemInstance.h"
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
    
    GameSubSystemInstance::GetInstance()->Create<Framelate>("Framelate")->RegisterGameSystem(gameUpdate::Type::Last, 256);
    return true;
}


/**============================================================================
//! @func   ShutDown
//! @brief  終了処理
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::ShutDown()
{
    //m_stageList.clear();
    return true;
}


/**============================================================================
//! @func   Initialaze
//! @brief  ゲームサブシステムの初期化
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::Initialaze()
{
    /**
     * サブシステムの更新順番を考慮して初期化を行う.
     */
    //for (auto& stage : m_stageList)
    //{
    //    for (auto& systemList : stage.second)
    //    {
    //        for (auto& system : systemList.second)
    //        {
    //            system.second->Initialize();
    //        }
    //    }
    //}

    /**
     * マネージャー初期化
     * 一斉に行う.
     */
    //game::ManagerInstance::Get().Initialize();
    return true;
}


/**============================================================================
//! @func   Run
//! @brief  ゲームの更新
//! @retval TRUE　成功終了/FALSE　失敗終了
============================================================================*/
bool systems::GameSystem::Run()
{
    for (auto& stage : m_stageList)
    {
        if (stage.first == gameUpdate::Type::None) break;
        
        for (auto& systemList : stage.second)
        {
            for (auto& system : systemList.second)
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
    /**
     * マネージャー終了処理
     */
    //game::ManagerInstance::Get().Releace();

    /**
     * ゲームサブシステムインスタンスで生成したものを一括で終了処理を行う
     * 終了処理に順番を考慮する必要が出てきたら初期化と同じ書き方にする必要が出てくる
     */
    //game::GameSubSystemInstance::Get().Releace();

    //m_stageList.clear();

    return true;
}

/**============================================================================
//! @func   AddSystem
//! @brief  システムを追加する
//! @param  set
============================================================================*/
void systems::GameSystem::AddSubSystem(GameSubSystemPtr set)
{
    gameUpdate::Type type = set->GetUpdateType();
    uInt64 priority = set->GetPriority();
    String name = set->GetName();
    m_stageList[type][priority][name] = set;
}