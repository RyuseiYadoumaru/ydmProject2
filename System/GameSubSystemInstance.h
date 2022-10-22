//******************************************************************************
//* @file   GameSubSystemInstance.h
//* @brief  ゲームサブシステムインスタンス
//* @note   全てのゲームサブシステムの生成、参照を行う
//* @note	ゲームのサブシステムの生成は重要な役割の担うので、基本的にここの初期化で生成する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "GameSubSysmte.h"
#include "Debug.h"


namespace gameSystems
{
	template<class T>
	concept TGameSubSystem = requires(T gameSubSystem)
	{
		gameSubSystem.Initialize();
		gameSubSystem.Run();
		gameSubSystem.Finalize();
		gameSubSystem.GetName();
		gameSubSystem.IsSingleton();
		gameSubSystem.IsRegistered();
	};

	class GameSubSystemInstance
	{
		SINGLETON_CLASS(GameSubSystemInstance);
		using GameSubSystemList = Unordered_Map <String, SharedPtr<GameSubSystem>>;

	public:
		/**============================================================================
		//! @func   Create
		//! @brief  ゲームサブシステムを生成
		============================================================================*/
		template<TGameSubSystem TYPE>
		SharedPtr<TYPE> Create(String name, bool isSingleton = true)
		{
			// シングルトンの場合同じデータ型がないか探索する
			for (auto& subsystem : m_gameSubSystems)
			{
				SharedPtr<TYPE> check = std::dynamic_pointer_cast<TYPE>(subsystem.second);
				if (check != nullptr)
				{
					if (check->IsSingleton() == true || isSingleton == true)
					{
						tools::Debug::LogWarning("シングルトンの為生成できません>>>>>>>", check->GetName());
						return nullptr;
					}
					break;
				}
			}
			
			// 同じ名前のシステムは生成しない
			if(m_gameSubSystems[name] != nullptr)
			{
				tools::Debug::LogError("ゲームサブシステムの名前が重複しています>>>>>>>", name);
				tools::Debug::Log("重複しない名前でゲームサブシステムを設定してください");
				return nullptr;
			}
			auto buff = std::make_shared<TYPE>(name, isSingleton);
			m_gameSubSystems.insert(std::make_pair(name, buff));
			return buff;
		}

		/**============================================================================
		//! @func   GetSubSystem
		//! @brief  サブシステム取得
		//! @note	ゲームシステムに登録されているものを参照する
		============================================================================*/
		template<TGameSubSystem TYPE>
		SharedPtr<TYPE> GetSubSystem(String systemName)
		{
			if (m_gameSubSystems.count(systemName) == 0)
			{
				tools::Debug::LogError("ゲームシステムの参照に失敗しました>>>>>>", systemName);
				return nullptr;
			}

			if (m_gameSubSystems[systemName]->IsRegistered() == false)
			{
				tools::Debug::LogError("ゲームシステムはシステムに登録されていません");
				return nullptr;
			}

			auto buff = std::dynamic_pointer_cast<TYPE>(m_gameSubSystems[systemName]);
			return buff;
		}

		/**============================================================================
		//! @func   Releace
		//! @brief  ゲームサブシステム解放処理
		============================================================================*/
		void Releace() noexcept
		{
			for (auto& system : m_gameSubSystems)
			{
				system.second->Finalize();
			}
			m_gameSubSystems.clear();
		}

	private:
		GameSubSystemList m_gameSubSystems;
	};
}





