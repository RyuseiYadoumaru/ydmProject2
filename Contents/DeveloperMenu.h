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
#include "Vector3.h"

namespace GAME_SYSTEMS
{
	class Line;
}

namespace EDITOR_SYSTEMS
{
	class DebugEditor;
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

		struct DebugCameraInfo
		{
			Int32 Priority = -1;
			MY_MATH::Vector3 Position;
			MY_MATH::Vector3 Rotation;
		};


	public:
		static void SetUp();
		static void ShutDown();

		static void ChangeType(Type type) noexcept;
		static const Type& GetType() noexcept { return m_type; }

		static SharedPtr<GAME_SYSTEMS::Line> GetLine() noexcept { return m_debugLine; }

		static const Int32& GetDebugCameraPriority() noexcept { return m_debugCameraInfo.Priority; }

	private:
		static DeveloperMenu::Type m_type;
		static SharedPtr<GAME_SYSTEMS::Line> m_debugLine;
		static DebugCameraInfo m_debugCameraInfo;

	private:
		friend EDITOR_SYSTEMS::DebugEditor;

		DeveloperMenu() = delete;
		~DeveloperMenu() = delete;
	};

}
