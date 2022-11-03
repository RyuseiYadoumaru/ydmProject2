//*****************************************************************************
//* @file   Easing.h
//* @brief  イージング関数をまとめたもの
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   October 2022
//*****************************************************************************
#pragma once
#include <cassert>
#include <DirectXMath.h>

namespace myMath
{
	class Easing
	{
	public:
		/**
		 * リニア：等速で変化する.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty Liner(float time, float totalTime, Ty min, Ty max) noexcept
		{
			return (max - min) * time / totalTime + min;
		}

		/**
		 * インサイン：徐々に加速していく.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty SineIn(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			return -max * cos(time * (PI * 90.0f / 180.0f) / totalTime) + max + min;
		}

		/**
		 * サインアウト：徐々に減速していく.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty SineOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			return max * sin(time * (PI * 90.0f / 180.0f) / totalTime) + min;
		}

		/**
		 * サインインアウト：徐々に上昇し徐々に減速していく.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty SineInOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			return -max / 2.0f * (cos(time * PI / totalTime) - 1.0f)+ min;
		}

		/**
		 * 緩やかに上昇する.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty QuadIn(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime;
			return max * time * time + min;
		}

		/**
		 * 緩やかに減速する.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty QuadOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime;
			return -max * time * (time - 2.0f) + min;
		}

		/**
		 * 緩やかに上昇し 緩やかに減速する.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty QuadInOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime / 2.0f;
			if (time < 1.0f) return max / 2.0f * time * time + min;
			time -= 1.0f;
			return -max / 2.0f * (time * (time - 2.0f) - 1.0f) + min;
		}

		/**
		 * まあまあ緩やかに上昇する.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty CubicIn(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime;
			return max * time * time * time + min;
		}

		/**
		 * まあまあ緩やかに減速する.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty CubicOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime - 1.0f;
			return max * (time * time * time + 1.0f) + min;
		}

		/**
		 * まあまあ緩やかに上昇し まあまあ緩やかに減速する.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty CubicInOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			assert(max > min);
			assert(time <= totalTime);
			max -= min;
			time /= totalTime / 2.0f;
			if (time < 1.0f) return max / 2.0f * time * time * time + min;
			time -= 2.0f;
			return max / 2.0f * (time * time * time + 2.0f) + min;
		}

		/**
		 * エキスポーメントイン：終盤に一気に上昇.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty ExpoIn(float time, float totalTime, Ty min, Ty max) noexcept
		{
			assert(max > min);
			assert(time <= totalTime);
			max -= min;
			return (time == 0.0f) ? min : max * pow(2.0f, 10.0f * (time / totalTime - 1.0f)) + min;
		}

		/**
		 * エキスポーメントアウト：序盤に一気に上昇.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty ExpoOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			assert(max > min);
			assert(time <= totalTime);
			max -= min;
			return (time == totalTime) ? (max + min) : max * (-pow(2.0f, -10.0f * time / totalTime) + 1.0f) + min;
		}

		/**
		 * エキスポーメントインアウト：中盤に一気に上昇.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty ExpoInOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			assert(max > min);
			assert(time <= totalTime);
			if (time == 0.0f) return min;
			if (time == totalTime) return max;
			max -= min;
			time /= totalTime / 2.0f;
			if (time < 1.0f) return max / 2.0f * pow(2.0f, 10.0f * (time - 1.0f)) + min;

			time -= 1.0f;
			return max / 2.0f * (-pow(2.0f, -10.0f * time) + 2.0f) + min;
		}



	private:
		constexpr static float PI = 3.141592653589793f;

	private:
		Easing() = delete;
		~Easing() = delete;
	};
}