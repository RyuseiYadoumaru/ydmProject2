//*****************************************************************************
//* @file   AudioSystem.h
//* @brief  �T�E���h�V�X�e��
//* @note   XAudio2���g�p
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include <xaudio2.h>
#include <wrl/client.h>
#include "std.h"
#include "macro.h"
#include "Core/SubSystem.h"
using Microsoft::WRL::ComPtr;

namespace systems
{
	class AudioSystem final : public SubSystem
	{
		SINGLETON_CLASS(AudioSystem);
	public:
		bool SetUp()	override;
		bool ShutDown() override;

	public:
		IXAudio2* GetIXAudio2() noexcept { return m_xAudio2.Get(); }
		IXAudio2MasteringVoice* GetXAudio2MasteringVoice() noexcept { return m_masteringVoice; }

	private:

		/**
		 * XAudio2�C���^�[�t�F�[�X
		 * �S�ẴI�[�f�B�I�G���W���̏�ԁA�����X���b�h�A�����O���t���Ǘ�����.
		 */
		ComPtr<IXAudio2> m_xAudio2 = nullptr;

		/**
		 * �}�X�^�����O�{�C�X
		 * �I�[�f�B�I�o�̓f�o�C�X��\���Ƃ��Ɏg�p����
		 * ComPtr���Ɠ�ɃG���[���������Ă��܂����ߕ��ʂ̃|�C���^�ϐ��ň����Ă܂�.
		 */
		IXAudio2MasteringVoice* m_masteringVoice = nullptr;

	};
}
