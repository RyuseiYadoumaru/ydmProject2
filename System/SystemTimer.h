//******************************************************************************
//* @file   SystemTimer.h
//* @brief  システムタイマークラス
//* @note   システム上の時間を管理する
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "std.h"
#include "macro.h"
#include "Core/SubSystem.h"

namespace systems
{
	class SystemTimer final : public SubSystem
	{
		SINGLETON_CLASS(SystemTimer);
	public:
		bool SetUp()	override;
		bool ShutDown() override;

		uInt64 GetTime() noexcept { return timeGetTime(); }
	public:
		constexpr static uInt32 m_FPS = 60;

	};
}