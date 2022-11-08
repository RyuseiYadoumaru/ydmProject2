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
#include "GameObjectManager.h"

#include "DirectXGraphics.h"
#include "../DX11Settransform.h"
#include "../Skeleton.h"


USING_GAME_SYSTEMS;

bool GAME_SYSTEMS::World::Initialize()
{
    // �V�[���}�l�[�W���[�Z�b�g�A�b�v
    SceneManager::GetInstance()->Setup();

    // �萔�o�b�t�@������
    DX11SetTransform::GetInstance()->Init();
    // ���p�̒萔�o�b�t�@������
    Skeleton::InitConstantBufferBoneMatrix(&systems::DirectXGraphics::GetInstance()->GetDevice());

    return true;
}

bool GAME_SYSTEMS::World::Run()
{
    auto sceneManager = SceneManager::GetInstance();
    auto gameObjectManager = GameObjectManager::GetInstance();

    if (sceneManager->GetSceneState() == SceneManager::State::Start)
    {
        sceneManager->SceneSetup();
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
        sceneManager->SceneShutdown();
    }
    return true;
}

bool GAME_SYSTEMS::World::Finalize()
{
    SceneManager::GetInstance()->Shutdown();
    Skeleton::UninitConstantBufferBoneMatrix();
    DX11SetTransform::GetInstance()->Uninit();
    return true;
}
