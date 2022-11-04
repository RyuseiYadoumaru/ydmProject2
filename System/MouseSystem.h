//*****************************************************************************
//* @file   MouseSystem.h
//* @brief  マウスシステム
//* @note   マウス入力周りの更新を行う
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************
#pragma once
#include <dinput.h>
#include "GameSubSysmte.h"
#include "macro.h"
#include "std.h"

namespace GAME_SYSTEMS
{
	class MouseSystem : public GameSubSystem
	{
		GAMESUBSYSTEM;

	public:
		DIMOUSESTATE& GetMouseState() noexcept { return m_mouseState; }
		DIMOUSESTATE& GetOldMouseState() noexcept { return m_oldMouseState; }

		bool Initialize() override;
		bool Run() override;
		bool Finalize() override;

	public:
		constexpr static Byte m_MaskInputMouseBuffer = 0x80;

	private:
		DIMOUSESTATE m_mouseState;		// マウス状態
		DIMOUSESTATE m_oldMouseState;	// 前フレームのマウス状態

	};
}
