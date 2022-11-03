//*****************************************************************************
//* @file   SceneManager.cpp
//* @brief	シーンマネージャークラス
//* @note   シーンを管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include "SceneManager.h"
#include "Scene.h"
#include "../Game/TestScene.h"


/**
 *  シーンリストからシーンを取得し、更新スタックに挿入します.
 * 
 * !@param sceneName	: ロードするシーン名
 * !@param isStackClear	: シーンを保存するスタックを破棄するフラグ
 */
void gameSystems::SceneManager::LoadScene(String sceneName, bool isStackClear)
{
	if (m_sceneList.contains(sceneName) == false) return;

	if (isStackClear == true)
	{
		while (m_enebleSceneStack.empty() == false)
		{
			// スタックが空になるまでポップする
			m_enebleSceneStack.pop();
		}
	}
	// 待機シーン
	m_standByScene = m_sceneList[sceneName];
}

void GAME_SYSTEMS::SceneManager::Setup()
{
	RegisterScene<TestScene>("TestScene");

	m_currentScene = m_sceneList["TestScene"];
}

void GAME_SYSTEMS::SceneManager::SceneSetup()
{
	// シーン初期化
	m_currentScene->Initialize();

	m_sceneState = State::Run;
}

void GAME_SYSTEMS::SceneManager::SceneRun()
{
	m_currentScene->Run();
}

void GAME_SYSTEMS::SceneManager::SceneShutdown()
{
	// シーン終了処理
	m_currentScene->Finalize();

	// 次のシーンに切り替える
	m_currentScene = m_standByScene;
	m_standByScene = nullptr;
	m_enebleSceneStack.push(m_currentScene->ToString());
	m_sceneState = State::Start;
}

void GAME_SYSTEMS::SceneManager::Shutdown()
{
	while (m_enebleSceneStack.empty() == false)
	{
		// スタックが空になるまでポップする
		m_enebleSceneStack.pop();
	}

	m_standByScene = nullptr;
	m_currentScene = nullptr;
	m_sceneList.clear();
}
