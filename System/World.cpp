//*****************************************************************************
//* @file   World.cpp
//* @brief  
//* @note   �Q�[���̃V�[����I�u�W�F�N�g�̏�����,�X�V���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "World.h"
#include "SceneManager.h"
USING_GAME_SYSTEMS;

bool GAME_SYSTEMS::World::Initialize()
{
    // �V�[���}�l�[�W���[�Z�b�g�A�b�v
    SceneManager::GetInstance()->Setup();
    return true;
}

bool GAME_SYSTEMS::World::Run()
{
    auto sceneManager = SceneManager::GetInstance();
    
    if (sceneManager->GetSceneState() == SceneManager::State::Start)
    {
        sceneManager->SceneSetup();
    }
    
    if (sceneManager->GetSceneState() == SceneManager::State::Run)
    {
        sceneManager->SceneRun();
    }

    if (sceneManager->GetSceneState() == SceneManager::State::End)
    {
        sceneManager->SceneShutdown();
    }
    return true;
}

bool GAME_SYSTEMS::World::Finalize()
{
    SceneManager::GetInstance()->Shutdown();
    return true;
}
