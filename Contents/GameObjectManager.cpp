//*****************************************************************************
//* @file   GameObjectManager.h
//* @brief  
//* @note   全てのオブジェクトを管理する
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
    m_destroyObjectList.emplace_back(gameObject);
}

bool GAME_SYSTEMS::GameObjectManager::GameObjectSetUp()
{
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::GameObjectStartUpdate()
{
    // スクリプト削除
    ScriptManager::GetInstance()->DestroyUpdate();

    // システムコンポーネント削除
    MiscellaneousManager::GetInstance()->DestroyUpdate();

    // 物理コンポーネント削除
    PhysicsManager::GetInstance()->DestroyUpdate();

    // グラフィックコンポーネント削除
    GraphicsManager::GetInstance()->DestroyUpdate();


    // オブジェクト削除
    for (auto& destroy : m_destroyObjectList)
    {
        m_gameObjectList.erase(destroy->m_id);
    }
    m_destroyObjectList.clear();
    // オブジェクト初期化
    for (auto& instance : m_instanceObjectList)
    {
        m_gameObjectList[instance->GetID()] = instance;
    }
    m_instanceObjectList.clear();

    // システムコンポーネント初期化
    MiscellaneousManager::GetInstance()->StartUpdate();

    // 物理コンポーネント初期化
    PhysicsManager::GetInstance()->StartUpdate();

    // グラフィックコンポーネント初期化
    GraphicsManager::GetInstance()->StartUpdate();

    // スクリプト初期化
    ScriptManager::GetInstance()->StartUpdate();
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::GameLogicUpdate()
{
    ScriptManager::GetInstance()->Update();
    return true;
}

bool GAME_SYSTEMS::GameObjectManager::ComponentUpdate()
{
    // システムコンポーネント
    MiscellaneousManager::GetInstance()->Update();

    // 物理更新
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