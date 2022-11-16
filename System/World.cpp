//*****************************************************************************
//* @file   World.cpp
//* @brief  
//* @note   �Q�[���̃V�[����I�u�W�F�N�g�̏�����,�X�V���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "World.h"
#include "ManagerInterface.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "MeshManager.h"


#include "DirectXGraphics.h"
#include "../System/DX11Settransform.h"
#include "Skeleton.h"


USING_GAME_SYSTEMS;

bool GAME_SYSTEMS::World::Initialize()
{
    // �}�l�[�W���[�Z�b�g�A�b�v
    ManagerInterface::SetUp();
    return true;
}

bool GAME_SYSTEMS::World::Run()
{
    auto sceneManager = SceneManager::GetInstance();
    auto gameObjectManager = GameObjectManager::GetInstance();

    if (sceneManager->GetSceneState() == SceneManager::State::Start)
    {
        sceneManager->SceneSetup();
        gameObjectManager->GameObjectStartUpdate();
        sceneManager->BeginPlay();

    }
    
    if (sceneManager->GetSceneState() == SceneManager::State::Run)
    {
        gameObjectManager->GameObjectStartUpdate();
        gameObjectManager->GameLogicUpdate();
        sceneManager->SceneRun();
        gameObjectManager->ComponentUpdate();
        sceneManager->SceneRendering();
    }

    if (sceneManager->GetSceneState() == SceneManager::State::End)
    {
        GameObjectManager::GetInstance()->GameObjectShutDown();
        MeshManager::GetInstance()->Releace();
        sceneManager->SceneShutdown();
    }
    return true;
}

bool GAME_SYSTEMS::World::Finalize()
{
    ManagerInterface::ShutDown();
    return true;
}
