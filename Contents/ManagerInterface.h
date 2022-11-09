//*****************************************************************************
//* @file   ManagerInterface.h
//* @brief  マネージャー関連のインターフェース
//* @note   各マネージャーのフレンドになります
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class ManagerInterface
	{
	public:
		static void SetUp();
		static void ShutDown();
	};
}
