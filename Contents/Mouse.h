//*****************************************************************************
//* @file   Mouse.h
//* @brief  マウス
//* @note   マウスの入力を管理する
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************
#pragma once
#include "Vector2.h"
#include "macro.h"
#include "std.h"
namespace GAME_SYSTEMS
{
	enum class MouseCode
	{
		Left = 0,	// 左クリック
		Right,		// 右クリック
		Center		// センターホイール
	};

	class Mouse
	{
	public:
		/**
		 * マウスクリック.
		 */
		static bool Click(MouseCode mouseCode);

		/**
		 * マウスクリックリリース.
		 */
		static bool Up(MouseCode mouseCode);

		/**
		 * カーソル座標取得.
		 */
		static myMath::Vector2 CursorPosition();


		/**
		 * カーソル移動量取得.
		 */
		static myMath::Vector2 CursorVelocity();

	};
}
