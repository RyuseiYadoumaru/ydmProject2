//*****************************************************************************
//* @file   DeveloperMenu.h
//* @brief  
//* @note   開発者用メニュー
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class Line;
}

namespace developer
{
	class DeveloperMenu
	{
	public:
		enum class Type
		{
			Master,
			Develop
		};

	public:
		static void SetUp();
		static void ShutDown();

		static void ChangeType(Type type) noexcept;
		static const Type& GetType() noexcept { return m_type; }

		static SharedPtr<GAME_SYSTEMS::Line> GetLine() noexcept { return m_debugLine; }


	private:
		static DeveloperMenu::Type m_type;
		static SharedPtr<GAME_SYSTEMS::Line> m_debugLine;

	private:
		DeveloperMenu() = delete;
		~DeveloperMenu() = delete;
	};

}
