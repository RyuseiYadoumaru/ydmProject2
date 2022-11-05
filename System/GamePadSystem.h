//*****************************************************************************
//* @file   GamePadSystem.h
//* @brief  ゲームパッドシステム
//* @note   ゲームパッドの入力周りの更新を行う
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once


#include "Inputsystem.h"
#include "GameSubSysmte.h"
#include "macro.h"
#include "std.h"

#include <xinput.h>
#pragma comment (lib, "xinput.lib")

namespace GAME_SYSTEMS
{
	class GamePadSystem : public GameSubSystem
	{
		GAMESUBSYSTEM;

	public:
		XINPUT_STATE& GetXinputState(uInt32 index = 0) noexcept { return m_xinputState[index]; }
		XINPUT_STATE& GetOldXinputState(uInt32 index = 0) noexcept { return m_oldXinputState[index]; }

	public:
		bool Initialize() override;
		bool Run() override;
		bool Finalize() override;

	private:
		constexpr static uInt32 m_gamePadMaxNum = 4;

	private:
		Array<XINPUT_STATE, m_gamePadMaxNum> m_xinputState;			// ゲームパッドステータス
		Array<XINPUT_STATE, m_gamePadMaxNum> m_oldXinputState;		// 前フレームのステータス

	};
}
