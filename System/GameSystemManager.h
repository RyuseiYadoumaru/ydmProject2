//******************************************************************************
//* @file   GameSubSystemManager.h
//* @brief  ゲームサブシステムマネージャー
//* @note   全てのゲームサブシステムの生成、参照を行う
//* @note	ゲームのサブシステムの生成は重要な役割の担うので、基本的にここの初期化で生成する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "Debug.h"
#include "GameSubSysmte.h"
#include "GameSystem.h"


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
	};

	class GameSystemManager
	{
		SINGLETON_CLASS(GameSystemManager);

		friend systems::GameSystem;

		using GameSubSystemPtr = SharedPtr<gameSystems::GameSubSystem>;
		 // サブシステムを管理するコンテナ->[優先度][システム名][ゲームサブシステム]
		using SubsystemContainer = Map<uInt64, Unordered_Map<String, GameSubSystemPtr>>;
		// システムのステージ->更新ステージ順
		using SystemStage = Map<gameUpdate::Type, SubsystemContainer>;

	public:
		/**============================================================================
		//! @func   Create
		//! @brief  ゲームサブシステムを生成
		============================================================================*/
		template<TGameSubSystem TYPE>
		SharedPtr<TYPE> Create(String name, gameUpdate::Type type, uInt32 priority = 128, bool isSingleton = true)
		{
			// シングルトンの場合同じデータ型がないか探索する
			for (auto& stage : m_gameSubSystemList)
			{
				for (auto& subSystemList : stage.second)
				{
					if (subSystemList.second.contains(name) == true)
					{
						// 名前が重複する場合優先度が違う場合でも除外する
						tools::Debug::LogError("ゲームサブシステムの名前が重複しています：", name);
						return nullptr;
					}

					for (auto& subSystem : subSystemList.second)
					{
						auto check = std::dynamic_pointer_cast<TYPE>(subSystem.second);
						if (check != nullptr)
						{
							if (check->IsSingleton() == true || isSingleton == true)
							{
								tools::Debug::LogWarning("シングルトンの為生成できません：", check->GetName());
								return nullptr;
							}
						}
					}
				}
			}
			auto buff = std::make_shared<TYPE>(name, priority, type, isSingleton);
			m_gameSubSystemList[type][priority][name] = buff;
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
			for (auto& stage : m_gameSubSystemList)
			{
				for (auto& subSystemList : stage.second)
				{
					if (subSystemList.second.contains(systemName) == true)
					{
						auto buff = std::dynamic_pointer_cast<TYPE>(subSystemList.second.at(systemName));
						return buff;
					}
				}
			}
			return nullptr;
		}

	public:
		void Releace();

	private:
		SystemStage m_gameSubSystemList;
	};
}





