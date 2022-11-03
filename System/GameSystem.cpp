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

    return true;
}


/**============================================================================
//! @func   ShutDown
//! @brief  �I������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::ShutDown()
{
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
//! @func   Finalize
//! @brief  �Q�[���I������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::GameSystemEnd()
{
    gameSystems::GameSystemManager::GetInstance()->Releace();
    return true;
}