//*****************************************************************************
//* @file   GameSubSysmte.h
//* @brief  ゲームサブシステムクラス
//* @note   ゲームシステムに必要なシステム
//* @note   継承して使ってください
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "GameSystem.h"
#include "std.h"
#include "macro.h"

#define GAMESUBSYSTEM using GameSubSystem::GameSubSystem;
namespace gameSystems
{
	class GameSubSystem : public std::enable_shared_from_this<GameSubSystem>
	{
	public:
		virtual bool Initialize()	= 0;
		virtual bool Run()			= 0;
		virtual bool Finalize()		= 0;

	public:
		String GetName() const noexcept { return m_name; }
		const gameUpdate::Type& GetUpdateType() const noexcept { return m_type; }
		const uInt64& GetPriority() const noexcept { return m_priority; }
		bool IsSingleton() const noexcept { return m_isSingleton; }

	public:
		explicit GameSubSystem(String name, uInt32 priority, gameUpdate::Type type, bool isSingleton) :
			m_name(name),
			m_priority(priority),
			m_type(type),
			m_isSingleton(isSingleton) {}
		~GameSubSystem() = default;

	private:
		String m_name;
		uInt64 m_priority;
		gameUpdate::Type m_type;
		bool m_isSingleton;
	};
}
