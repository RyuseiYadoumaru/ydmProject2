//*****************************************************************************
//* @file   GameSystem.h
//* @brief  ゲームシステムクラス
//* @note   ゲームシステムに必要なシステムを管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "SubSystem.h"
#include "std.h"
#include "macro.h"

namespace gameSystems
{
	class Subsystem;
	class GameSubSystem;
	class Manager;
}

namespace gameUpdate
{
	enum class Type
	{
		/**
		* システム更新.
		*/
		System	= 0,
		
		/**
		* メイン更新.
		*/
		Main	= 1,
		
		/**
		 * 最後に行う更新.
		 */
		Last	= 2,

		/**
		 * 更新なし.
		 */
		None,
	};
}

namespace systems
{
	class GameSystem : public SubSystem
	{
		SINGLETON_CLASS(GameSystem);

		/**
		 * GameSubsystemのポインタ.
		 */
		using GameSubSystemPtr = SharedPtr<gameSystems::GameSubSystem>;

		/**
		 * システムステージ.
		 */
		// サブシステムを管理するコンテナ->[優先度][システム名][ゲームサブシステム]
		using SubsystemContainer	= Map<uInt64, Unordered_Map<String, GameSubSystemPtr>>;
		// システムのステージ->更新ステージ順
		using SystemStage			= Map<gameUpdate::Type, SubsystemContainer>;

	public:
		bool SetUp()	override;
		bool ShutDown() override;
		bool Run();
		bool Initialaze();
		bool Finalize();

	private:
		void AddSubSystem(GameSubSystemPtr set);

	private:
		SystemStage m_stageList;
		friend gameSystems::GameSubSystem;

	};
}
