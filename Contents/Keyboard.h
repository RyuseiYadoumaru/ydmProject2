//******************************************************************************
//* @file   Keyboard.h
//* @brief  キーボード
//* @note   キーボード入力を管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "Keycode.h"
#include "macro.h"
#include "std.h"

namespace GAME_SYSTEMS
{
	class KeyboardSystem;

	class Keyboard
	{
	public:
		/**
		 * キーボードプレス入力.
		 */
		static bool Press(Keycode input);
		
		/**
		 * キーボードリリース入力.
		 * 現在はトリガーの処理になっている.
		 */
		static bool Releace(Keycode input);
		
		
		/**
		 * キーボードトリガー入力
		 */
		static bool Trigger(Keycode input);
	};

}
