//*****************************************************************************
//* @file   SceneManager.h
//* @brief	シーンマネージャークラス
//* @note   シーンを管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "../System/World.h"

namespace GAME_SYSTEMS
{
	class Scene;
	using ScenePtr = SharedPtr<Scene>;

	template<class T>
	concept TScene = requires(T & scene)
	{
		scene.Initialize();
		scene.Run();
		scene.Finalize();
		scene.GetDisPlayColor();
	};

	class SceneManager
	{
		SINGLETON_CLASS(SceneManager);

	public:
		enum class State
		{
			Start,
			Run,
			End
		};

	public:
		void LoadScene(String sceneName, bool isStackClear = false);
		
		template<TScene Type>
		void RegisterScene(String sceneName)
		{
			ScenePtr scene = std::make_shared<Type>(sceneName);
			m_sceneList.insert(std::make_pair(sceneName, scene));
		}
	public:
		// シーン名取得
		const String& GetSceneName() const noexcept { return m_enebleSceneStack.top(); }

		// シーンステート取得
		const SceneManager::State& GetSceneState() const noexcept { return m_sceneState; }

	private:
		void Setup();
		void SceneSetup();
		void BeginPlay();
		void SceneRun();
		void SceneRendering();
		void SceneShutdown();
		void Shutdown();

	private:
		// シーン
		ScenePtr m_currentScene;
		ScenePtr m_standByScene;

		// 管理用コンテナ
		Unordered_Map<String ,ScenePtr> m_sceneList;
		Stack<String> m_enebleSceneStack;

		// シーンステート
		State m_sceneState;

	private:
		friend World;
	};
}
