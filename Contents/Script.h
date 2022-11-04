//*****************************************************************************
//* @file   Script.h
//* @brief  
//* @note   �X�N���v�g�x�[�X���p�����āA�̃I�u�W�F�N�g�̏���������
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
	class GameObjectManager;

	class Script : public systems::Component
	{
		using ScriptContainer = Map<uInt32, Unordered_Map<uInt32, Script*>>;

	public:
		Script() : systems::Component("Script", true) {}
		~Script() = default;

	private:
		static bool ScriptUpdate();
		static bool ScriptReleace();

	private:
		static ScriptContainer m_scriptList;

	public:
		void Initialize() override;
		void Finalize() override;

	protected:
		virtual void Setting() {}
		virtual void Start()	= 0;
		virtual void Update()	= 0;
		virtual void End()		= 0;

	protected:
		uInt32 m_priority = 128;

	protected:
		friend gameSystems::GameObjectManager;
		friend gameSystems::GameObject;

	};
}