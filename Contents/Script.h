//*****************************************************************************
//* @file   Script.h
//* @brief  
//* @note   スクリプトベースを継承して、のオブジェクトの処理を書く
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "../System/Core/Component.h"

#define SCRIPT_CLASS gameSystems::Script::Script;

namespace GAME_SYSTEMS
{
	class ScriptManager;
	class GameObjectManager;

	class Script : public systems::Component
	{
	public:
		explicit Script() : systems::Component("Script", true) {}
		explicit Script(Int32 priority) :
			systems::Component("Script", true),
		m_priority(priority){}
		~Script() = default;

	public:
		void Initialize() override;
		void Finalize() override;

		void SetPriority(Int32 priority) noexcept { m_priority = priority; }

	protected:
		virtual void Start()	= 0;
		virtual void Update()	= 0;
		virtual void End()		= 0;

	protected:
		Int32 m_priority = 128;

	protected:
		friend ScriptManager;
		friend gameSystems::GameObjectManager;
		friend gameSystems::GameObject;

	};
}