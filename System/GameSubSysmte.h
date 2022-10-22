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
		/**
		 *  ゲームシステムに登録.
		 * 
		 * !@param type
		 * !@param priority
		 * !@param isSingleton
		 */
		void RegisterGameSystem(gameUpdate::Type type, uInt64 priority = 128)
		{
			m_type = type;
			m_priority = priority;
			m_isRegistered = true;
			systems::GameSystem::GetInstance()->AddSubSystem(shared_from_this());
		}

	public:
		String GetName() const noexcept { return m_name; }
		const gameUpdate::Type& GetUpdateType() const noexcept { return m_type; }
		const uInt64& GetPriority() const noexcept { return m_priority; }
		bool IsRegistered() const noexcept { return m_isRegistered; }
		bool IsSingleton() const noexcept { return m_isSingleton; }

	public:
		explicit GameSubSystem(String name, bool isSingleton) : 
			m_name(name),
			m_priority(128),
			m_type(gameUpdate::Type::None),
			m_isSingleton(isSingleton),
			m_isRegistered(false) {}
		~GameSubSystem() = default;

	private:
		String m_name;
		uInt64 m_priority;
		gameUpdate::Type m_type;
		bool m_isSingleton;
		bool m_isRegistered;
	};
}
