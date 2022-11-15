//*****************************************************************************
//* @file   Timer.h
//* @brief  �^�C�}�[�N���X
//* @note   ���Ԏ�����Ǘ�����
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
		 * �f���^�^�C�����擾����.
		 */
		static const Float32 DeltaTime() noexcept;

		/**
		 * �X�P�[���Ȃ��f���^�^�C�����擾����.
		 */
		static const Float32 UnScaleDeltaTime() noexcept;

		/**
		 * �Œ�̃f���^�^�C�����擾����.
		 */
		static const Float32 FixDeltaTime() noexcept;


		/**
		 * �t���[���J�E���g�擾����.
		 */
		static const uInt64 FrameCount() noexcept;

		/**
		 * �A�v���P�[�V�������N�����Ă���̌o�ߎ���.
		 */
		static const Float64 TotalTime() noexcept;

		/**
		 * �A�v���P�[�V�������N�����Ă���̌o�ߎ��ԁi�X�P�[���Ȃ��j.
		 */
		static const Float64 UnScaleTotlaTime() noexcept;


		/**
		 * �^�C���X�P�[���ݒ�.
		 */
		static void SetTimeScale(Float32 setScale) noexcept;

		/**
		 * �^�C���X�P�[���擾.
		 */
		static const Float32 TimeScale() noexcept;


		/**
		 * �Œ�t���[���t���O�擾.
		 */

		static const bool GetIsFixed()  noexcept;

	private:
		constexpr static Float32 m_maxTimeScale = 10.0f;
		constexpr static Float32 m_minTimeScale = 0.01f;
	};
}
