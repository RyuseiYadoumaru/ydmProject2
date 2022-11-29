//*****************************************************************************
//* @file   SceneManager.h
//* @brief	�V�[���}�l�[�W���[�N���X
//* @note   �V�[�����Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "ManagerHeader.h"
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
		MANAGER_CLASS;

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
		// �V�[�����擾
		const String& GetSceneName() const noexcept { return m_enebleSceneStack.top(); }

		// �V�[���X�e�[�g�擾
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
		// �V�[��
		ScenePtr m_currentScene = nullptr;
		ScenePtr m_standByScene = nullptr;

		// �Ǘ��p�R���e�i
		Unordered_Map<String ,ScenePtr> m_sceneList;
		Stack<String> m_enebleSceneStack;

		// �V�[���X�e�[�g
		State m_sceneState = State::Start;

	private:
		friend World;
	};
}
