//*****************************************************************************
//* @file   GameSystem.cpp
//* @brief  �Q�[���V�X�e���N���X
//* @note   �Q�[���V�X�e���ɕK�v�ȃT�u�V�X�e���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include "GameSystem.h"
#include "GameSystemManager.h"
#include "Framelate.h"
#include "World.h"
#include "KeyboardSystem.h"
#include "MouseSystem.h"
#include "GamePadSystem.h"
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
//! @brief  ������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::SetUp()
{
    GameSystemManager::GetInstance()->Create<Framelate>("Framelate", gameUpdate::Type::Last, 255, true);
    GameSystemManager::GetInstance()->Create<World>("World", gameUpdate::Type::Main, 128, true);
    GameSystemManager::GetInstance()->Create<KeyboardSystem>("KeyboardSystem", gameUpdate::Type::System, 0, true);
    GameSystemManager::GetInstance()->Create<MouseSystem>("MouseSystem", gameUpdate::Type::System, 1, true);
    GameSystemManager::GetInstance()->Create<GamePadSystem>("GamePadSystem", gameUpdate::Type::System, 2, true);

    return true;
}


/**============================================================================
//! @func   ShutDown
//! @brief  �I������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::ShutDown()
{
    auto gameSystem = GameSystemManager::GetInstance();
    gameSystem->m_gameSubSystemList.clear();
    return true;
}


/**============================================================================
//! @func   Initialaze
//! @brief  �Q�[���T�u�V�X�e���̏�����
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::GameSystemStart()
{
    auto gameSystem = GameSystemManager::GetInstance();
    // �T�u�V�X�e���̍X�V���Ԃŏ��������s����
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
//! @brief  �Q�[���̍X�V
//! @retval TRUE�@�����I��/FALSE�@���s�I��
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
//! @func   GameSystemEnd
//! @brief  �Q�[���T�u�V�X�e���I������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::GameSystemEnd()
{
    auto gameSystem = GameSystemManager::GetInstance();
    for (auto& stage : gameSystem->m_gameSubSystemList)
    {
        for (auto& subSystem : stage.second)
        {
            for (auto& system : subSystem.second)
            {
                system.second->Finalize();
            }
        }
    }
    return true;
}