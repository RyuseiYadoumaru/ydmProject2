//******************************************************************************
//* @file   State.h
//* @brief  
//* @note  　ステートの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "Std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class StateBase
	{
	public:
		StateBase() = default;
		~StateBase() = default;

	public:
		virtual void EnterState() = 0;
		virtual void ExitState() = 0;
		virtual void Update() = 0;
	};
}
