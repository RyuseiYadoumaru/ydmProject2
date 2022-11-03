//*****************************************************************************
//* @file   Easing.h
//* @brief  �C�[�W���O�֐����܂Ƃ߂�����
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
		 * ���j�A�F�����ŕω�����.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty Liner(float time, float totalTime, Ty min, Ty max) noexcept
		{
			return (max - min) * time / totalTime + min;
		}

		/**
		 * �C���T�C���F���X�ɉ������Ă���.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty SineIn(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			return -max * cos(time * (PI * 90.0f / 180.0f) / totalTime) + max + min;
		}

		/**
		 * �T�C���A�E�g�F���X�Ɍ������Ă���.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty SineOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			return max * sin(time * (PI * 90.0f / 180.0f) / totalTime) + min;
		}

		/**
		 * �T�C���C���A�E�g�F���X�ɏ㏸�����X�Ɍ������Ă���.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty SineInOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			return -max / 2.0f * (cos(time * PI / totalTime) - 1.0f)+ min;
		}

		/**
		 * �ɂ₩�ɏ㏸����.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty QuadIn(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime;
			return max * time * time + min;
		}

		/**
		 * �ɂ₩�Ɍ�������.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty QuadOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime;
			return -max * time * (time - 2.0f) + min;
		}

		/**
		 * �ɂ₩�ɏ㏸�� �ɂ₩�Ɍ�������.
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
		 * �܂��܂��ɂ₩�ɏ㏸����.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty CubicIn(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime;
			return max * time * time * time + min;
		}

		/**
		 * �܂��܂��ɂ₩�Ɍ�������.
		 */
		template<class Ty = float>
		[[nodiscard]] static Ty CubicOut(float time, float totalTime, Ty min, Ty max) noexcept
		{
			max -= min;
			time /= totalTime - 1.0f;
			return max * (time * time * time + 1.0f) + min;
		}

		/**
		 * �܂��܂��ɂ₩�ɏ㏸�� �܂��܂��ɂ₩�Ɍ�������.
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
		 * �G�L�X�|�[�����g�C���F�I�ՂɈ�C�ɏ㏸.
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
		 * �G�L�X�|�[�����g�A�E�g�F���ՂɈ�C�ɏ㏸.
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
		 * �G�L�X�|�[�����g�C���A�E�g�F���ՂɈ�C�ɏ㏸.
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