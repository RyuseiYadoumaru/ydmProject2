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
#include "Physics.h"
#include "Graphics.h"
#include "Script.h"

void GAME_SYSTEMS::GameObjectManager::Destroy(GameObjectPtr gameObject)
{
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
        destroy->ComponentEnd();
    }

    // �I�u�W�F�N�g�o�^
    for (auto& instance : m_instanceObjectList)
    {
        m_gameObjectList[instance->GetID()] = instance;
    }

    // �I�u�W�F�N�g������
    for (auto& instance : m_instanceObjectList)
    {
        instance->ComponentStart();
    }

    m_instanceObjectList.clear();
    m_destroyObjectList.clear();

    return true;
}

bool GAME_SYSTEMS::GameObjectManager::GameLogicUpdate()
{
    Script::ScriptUpdate();
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::ComponentUpdate()
{
    Physics::PhysicsUpdate();
    //Graphics::GraphicsUpdate();
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::GameObjectShutDown()
{
    for (auto& object : m_gameObjectList)
    {
        object.second->ComponentEnd();
        object.second->ShutDown();
    }

    Physics::PhysicsReleace();
    Graphics::GraphicsReleace();
    Script::ScriptReleace();
   
    m_destroyObjectList.clear();
    m_instanceObjectList.clear();
    m_gameObjectList.clear();
    return true;
}