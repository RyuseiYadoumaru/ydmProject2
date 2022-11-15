//*****************************************************************************
//* @file   Timer.h
//* @brief  タイマークラス
//* @note   時間周りを管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"

namespace GAME_SYSTEMS
{
	class Timer
	{
	public:

		/**
		 * デルタタイムを取得する.
		 */
		static const Float32 DeltaTime() noexcept;

		/**
		 * スケールなしデルタタイムを取得する.
		 */
		static const Float32 UnScaleDeltaTime() noexcept;

		/**
		 * 固定のデルタタイムを取得する.
		 */
		static const Float32 FixDeltaTime() noexcept;


		/**
		 * フレームカウント取得する.
		 */
		static const uInt64 FrameCount() noexcept;

		/**
		 * アプリケーションを起動してからの経過時間.
		 */
		static const Float64 TotalTime() noexcept;

		/**
		 * アプリケーションを起動してからの経過時間（スケールなし）.
		 */
		static const Float64 UnScaleTotlaTime() noexcept;


		/**
		 * タイムスケール設定.
		 */
		static void SetTimeScale(Float32 setScale) noexcept;

		/**
		 * タイムスケール取得.
		 */
		static const Float32 TimeScale() noexcept;


		/**
		 * 固定フレームフラグ取得.
		 */

		static const bool GetIsFixed()  noexcept;

	private:
		constexpr static Float32 m_maxTimeScale = 10.0f;
		constexpr static Float32 m_minTimeScale = 0.01f;
	};
}
