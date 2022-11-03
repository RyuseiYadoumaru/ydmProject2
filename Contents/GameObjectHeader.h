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
#include "Component.h"

namespace GAME_SYSTEMS
{
	template <class T>
	concept TComponent = requires(T & comp)
	{
		comp.Initialize();
		comp.Finalize();
	};

	using ComponentPtr = SharedPtr<Component>;
	using ComponentContainer = List<ComponentPtr>;

	template<TComponent T>
	using TComponentPtr = SharedPtr<T>;

}