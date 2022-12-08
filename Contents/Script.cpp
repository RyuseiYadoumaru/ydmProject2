//*****************************************************************************
//* @file   Script.cpp
//* @brief  
//* @note   スクリプトベースを継承して、のオブジェクトの処理を書く
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Script.h"
#include "GameObject.h"
#include "../System/ScriptManager.h"
USING_GAME_SYSTEMS;

void Script::Initialize()
{
	ScriptManager::GetInstance()->Register(this);
}

void GAME_SYSTEMS::Script::Finalize()
{
	ScriptManager::GetInstance()->Remove(this);
}
