//*****************************************************************************
//* @file   SceneHelper.h
//* @brief  
//* @note   シーンのヘッダーファイルで定義する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "Scene.h"
#include "macro.h"
#include "std.h"

namespace GAME_SYSTEMS
{
	class GameObject;
	class Script;
	class DefaultCamera;
}

using GameObjectPtr = SharedPtr<gameSystems::GameObject>;

