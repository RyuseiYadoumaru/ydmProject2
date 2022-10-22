//*****************************************************************************
//* @file   SubSystem.h
//* @brief  サブシステム
//* @note   アプリケーションに付随するシステムの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   October 2022
//*****************************************************************************
#pragma once
#include "std.h"

namespace systems
{
	class SubSystem
	{
	public:
		virtual bool SetUp()	= 0;
		virtual bool ShutDown() = 0;
	};
}
