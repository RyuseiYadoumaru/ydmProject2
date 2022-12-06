//*****************************************************************************
//* @file   GameObjectManager.h
//* @brief  
//* @note   �S�ẴI�u�W�F�N�g���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Miscellaneous.h"
#include "Physics.h"
#include "Graphics.h"
#include "Script.h"

#include "../System/MiscellaneousManager.h"
#include "../System/PhysicsManager.h"
#include "../System/GraphicsManager.h"
#include "../System/ScriptManager.h"

void GAME_SYSTEMS::GameObjectManager::Destroy(GameObjectPtr gameObject)
{
    gameObject->ShutDown();
    m_destroyObjectList.push_back(gameObject);
}

bool GAME_SYSTEMS::GameObjectManager::GameObjectSetUp()
{
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::GameObjectStartUpdate()
{
    // �I�u�W�F�N�g�폜
    for (auto& destroy : m_destroyObjectList)
    {
        m_gameObjectList.erase(destroy->m_id);
    }
    m_destroyObjectList.clear();

    // �I�u�W�F�N�g������
    for (auto& instance : m_instanceObjectList)
    {
        m_gameObjectList[instance->GetID()] = instance;
    }
    m_instanceObjectList.clear();

    // �V�X�e���R���|�[�l���g������
    MiscellaneousManager::GetInstance()->FirstUpdate();

    // �����R���|�[�l���g������
    PhysicsManager::GetInstance()->FirstUpdate();

    // �O���t�B�b�N�R���|�[�l���g������
    GraphicsManager::GetInstance()->FirstUpdate();

    // �X�N���v�g������
    ScriptManager::GetInstance()->FirstUpdate();
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::GameLogicUpdate()
{
    ScriptManager::GetInstance()->Update();
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::ComponentUpdate()
{
    // �V�X�e���R���|�[�l���g
    MiscellaneousManager::GetInstance()->Update();

    // �����X�V
    PhysicsManager::GetInstance()->Update();
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::GameObjectShutDown()
{
    for (auto& object : m_gameObjectList)
    {
        object.second->ShutDown();
    }
    m_destroyObjectList.clear();
    m_instanceObjectList.clear();
    m_gameObjectList.clear();

    MiscellaneousManager::GetInstance()->Releace();
    PhysicsManager::GetInstance()->Releace();
    GraphicsManager::GetInstance()->Releace();
    ScriptManager::GetInstance()->Releace();
   
    return true;
}