//*****************************************************************************
//* @file   GameSystem.cpp
//* @brief  �Q�[���V�X�e���N���X
//* @note   �Q�[���V�X�e���ɕK�v�ȃT�u�V�X�e���Ǘ�����
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
//! @brief  ������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::SetUp()
{
    
    GameSubSystemInstance::GetInstance()->Create<Framelate>("Framelate")->RegisterGameSystem(gameUpdate::Type::Last, 256);
    return true;
}


/**============================================================================
//! @func   ShutDown
//! @brief  �I������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::ShutDown()
{
    //m_stageList.clear();
    return true;
}


/**============================================================================
//! @func   Initialaze
//! @brief  �Q�[���T�u�V�X�e���̏�����
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::Initialaze()
{
    /**
     * �T�u�V�X�e���̍X�V���Ԃ��l�����ď��������s��.
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
     * �}�l�[�W���[������
     * ��Ăɍs��.
     */
    //game::ManagerInstance::Get().Initialize();
    return true;
}


/**============================================================================
//! @func   Run
//! @brief  �Q�[���̍X�V
//! @retval TRUE�@�����I��/FALSE�@���s�I��
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
//! @brief  �Q�[���I������
//! @retval TRUE�@�����I��/FALSE�@���s�I��
============================================================================*/
bool systems::GameSystem::Finalize()
{
    /**
     * �}�l�[�W���[�I������
     */
    //game::ManagerInstance::Get().Releace();

    /**
     * �Q�[���T�u�V�X�e���C���X�^���X�Ő����������̂��ꊇ�ŏI���������s��
     * �I�������ɏ��Ԃ��l������K�v���o�Ă����珉�����Ɠ����������ɂ���K�v���o�Ă���
     */
    //game::GameSubSystemInstance::Get().Releace();

    //m_stageList.clear();

    return true;
}

/**============================================================================
//! @func   AddSystem
//! @brief  �V�X�e����ǉ�����
//! @param  set
============================================================================*/
void systems::GameSystem::AddSubSystem(GameSubSystemPtr set)
{
    gameUpdate::Type type = set->GetUpdateType();
    uInt64 priority = set->GetPriority();
    String name = set->GetName();
    m_stageList[type][priority][name] = set;
}