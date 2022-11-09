//*****************************************************************************
//* @file   GameSystem.h
//* @brief  ゲームシステムクラス
//* @note   ゲームシステムに必要なシステムを管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "Core/SubSystem.h"
#include "std.h"
#include "macro.h"

namespace gameSystems
{
	class Subsystem;
	class GameSubSystem;
	class GameSystemManager;
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

	public:
		bool SetUp()	override;
		bool ShutDown() override;
		bool Run();
		bool GameSystemStart();
		bool GameSystemEnd();

	};
}
