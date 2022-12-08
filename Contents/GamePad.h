//*****************************************************************************
//* @file   GamePad.h
//* @brief  
//* @note   ゲームパッドの入力を管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once

#include "Vector2.h"
#include "macro.h"
#include "std.h"

#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

namespace GAME_SYSTEMS
{
	enum class Xinput
	{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,

		Up	  = XINPUT_GAMEPAD_DPAD_UP,
		Down  = XINPUT_GAMEPAD_DPAD_DOWN,
		Left  = XINPUT_GAMEPAD_DPAD_LEFT,
		Right = XINPUT_GAMEPAD_DPAD_RIGHT,

		Start	  = XINPUT_GAMEPAD_START,
		Back  = XINPUT_GAMEPAD_BACK,


		LeftThumb		= XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb		= XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder	= XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder	= XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	class GamePad
	{


	public:
		static bool Press(Xinput input, uInt32 index = 0);
		static bool Trigger(Xinput input, uInt32 index = 0);
		static bool Releace(Xinput input, uInt32 index = 0);


		static myMath::Vector2 LeftStick(uInt32 index = 0);
		static Float32 LeftStickAngle(uInt32 index = 0);
		static myMath::Vector2 RightStick(uInt32 index = 0);
		static Float32 RightStickAngle(uInt32 index = 0);

		static Float32 LeftTrigger(uInt32 index = 0);
		static Float32 RightTrigger(uInt32 index = 0);
		static Float32 OldLeftTrigger(uInt32 index = 0);
		static Float32 OldRightTrigger(uInt32 index = 0);

	public:
		constexpr static uInt32 m_XinputLeftVibrationMax = (0xffff * 0x02);
		constexpr static uInt32 m_XinputRightVibrationMax = (0xffff);
		constexpr static uInt32 m_XinputLeftThubmDeadZone = (7849);
		constexpr static uInt32 m_XinputRightThubmDeadZone = (8689);
		constexpr static Float32 m_XinputTriggerMax = 1.0f;
		constexpr static Float32 m_XinputStickMax = 1.0f;

	private:
		constexpr static Float32 m_stickMax		= 32767.0f;
		constexpr static Float32 m_triggerMax	= 255.0f;
	};

}
