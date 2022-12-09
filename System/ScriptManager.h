//*****************************************************************************
//* @file   ScriptManager.h
//* @brief  
//* @note   スクリプトの更新を管理する
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "Script.h"

namespace GAME_SYSTEMS
{
	class ScriptManager
	{
		SINGLETON_CLASS(ScriptManager);

	public:
		bool StartUpdate()
		{
			for (auto& scriptStage : m_instanceList)
			{
				for (auto& script : scriptStage.second)
				{
					script->Start();
					m_scriptList[script->m_priority][script->m_id] = script;
					script = nullptr;
				}
			}
			m_instanceList.clear();
			return true;
		}

		bool DestroyUpdate()
		{
			for (auto& scriptStage : m_destroyList)
			{
				for (auto& script : scriptStage.second)
				{
					script->End();
					script = nullptr;
				}
			}
			m_destroyList.clear();
			return true;
		}

		bool Update()
		{
			for (auto& scriptStage : m_scriptList)
			{
				for (auto& script : scriptStage.second)
				{
					script.second->Update();
				}
			}
			return true;
		}

		bool Releace()
		{
			for (auto& scriptStage : m_destroyList)
			{
				for (auto& script : scriptStage.second)
				{
					script->End();
					script = nullptr;
				}
			}
			for (auto& scriptStage : m_scriptList)
			{
				for (auto& script : scriptStage.second)
				{
					script.second->End();
					script.second = nullptr;
				}
			}
			m_scriptList.clear();
			m_instanceList.clear();
			m_destroyList.clear();
			return true;
		}

	public:
		void Register(Script* script)
		{
			m_instanceList[script->m_priority].emplace_back(script);
		}

		void Remove(Script* script)
		{
			m_destroyList[script->m_priority].emplace_back(script);
			m_scriptList[script->m_priority].erase(script->m_id);
		}

	private:
		Map<Int32, Vector<Script*>> m_instanceList;
		Map<Int32, Vector<Script*>> m_destroyList;
		Map<Int32, Unordered_Map<uInt32, Script*>> m_scriptList;
	};
}
