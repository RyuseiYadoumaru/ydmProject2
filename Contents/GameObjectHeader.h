//*****************************************************************************
//* @file   GameObjectHeader.h
//* @brief  
//* @note   ゲームオブジェクトに必要なヘッダー
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "../System/Core/Object.h"
#include "../System/Core/Component.h"
#include "Transform.h"
#include "Camera.h"

namespace GAME_SYSTEMS
{
	template <class T>
	concept TComponent = requires(T & comp)
	{
		comp.GetOwner();
	};

	class Script;
	class GameObjectManager;

	using ComponentPtr = SharedPtr<systems::Component>;
	using ComponentContainer = List<ComponentPtr>;

	template<TComponent T>
	using TComponentPtr = SharedPtr<T>;

}