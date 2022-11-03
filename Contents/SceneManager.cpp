//*****************************************************************************
//* @file   SceneManager.cpp
//* @brief	�V�[���}�l�[�W���[�N���X
//* @note   �V�[�����Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include "SceneManager.h"
#include "Scene.h"
#include "../Game/TestScene.h"


/**
 *  �V�[�����X�g����V�[�����擾���A�X�V�X�^�b�N�ɑ}�����܂�.
 * 
 * !@param sceneName	: ���[�h����V�[����
 * !@param isStackClear	: �V�[����ۑ�����X�^�b�N��j������t���O
 */
void gameSystems::SceneManager::LoadScene(String sceneName, bool isStackClear)
{
	if (m_sceneList.contains(sceneName) == false) return;

	if (isStackClear == true)
	{
		while (m_enebleSceneStack.empty() == false)
		{
			// �X�^�b�N����ɂȂ�܂Ń|�b�v����
			m_enebleSceneStack.pop();
		}
	}
	// �ҋ@�V�[��
	m_standByScene = m_sceneList[sceneName];
}

void GAME_SYSTEMS::SceneManager::Setup()
{
	RegisterScene<TestScene>("TestScene");

	m_currentScene = m_sceneList["TestScene"];
}

void GAME_SYSTEMS::SceneManager::SceneSetup()
{
	// �V�[��������
	m_currentScene->Initialize();

	m_sceneState = State::Run;
}

void GAME_SYSTEMS::SceneManager::SceneRun()
{
	m_currentScene->Run();
}

void GAME_SYSTEMS::SceneManager::SceneShutdown()
{
	// �V�[���I������
	m_currentScene->Finalize();

	// ���̃V�[���ɐ؂�ւ���
	m_currentScene = m_standByScene;
	m_standByScene = nullptr;
	m_enebleSceneStack.push(m_currentScene->ToString());
	m_sceneState = State::Start;
}

void GAME_SYSTEMS::SceneManager::Shutdown()
{
	while (m_enebleSceneStack.empty() == false)
	{
		// �X�^�b�N����ɂȂ�܂Ń|�b�v����
		m_enebleSceneStack.pop();
	}

	m_standByScene = nullptr;
	m_currentScene = nullptr;
	m_sceneList.clear();
}
