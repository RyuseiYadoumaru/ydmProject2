#include "Script.h"
#include "GameObject.h"
USING_GAME_SYSTEMS;

Script::ScriptContainer Script::m_scriptList;



bool GAME_SYSTEMS::Script::ScriptUpdate()
{
	for (auto& scriptList : m_scriptList)
	{
		for (auto& script : scriptList.second)
		{
			script.second->Update();
		}
	}
	return true;
}

bool GAME_SYSTEMS::Script::ScriptReleace()
{
	m_scriptList.clear();
	return true;
}

void Script::Initialize()
{
	// スクリプト設定
	Setting();
	
	// オブジェクト追加
	auto owner = GetOwner();
	m_scriptList[m_priority][owner->GetID()] = this;
}

void GAME_SYSTEMS::Script::Finalize()
{
	m_scriptList[m_priority].erase(m_id);
}
