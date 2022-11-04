//*****************************************************************************
//* @file   KeyboardSystem.h
//* @brief  �L�[�{�[�h�V�X�e��
//* @note   �L�[���͎���̍X�V���s��
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once

#include "GameSubSysmte.h"

namespace GAME_SYSTEMS
{
	class KeyboardSystem : public GameSubSystem
	{
		GAMESUBSYSTEM;
	public:
		bool Initialize() override;
		bool Run() override;
		bool Finalize() override;

		const Byte GetKeyBuffer(Byte buffer)	const noexcept { return m_keyBuffer[buffer]; }
		const Byte GetOldKeyBuffer(Byte buffer) const noexcept { return m_oldKeyBuffer[buffer]; }
	
	public:
		constexpr static uInt32 m_KeyBufferSize	= 256;
		constexpr static Byte m_MaskInputKeyboardBuffer = 0x80;

	private:
		Byte m_keyBuffer[256] = { 0 };
		Byte m_oldKeyBuffer[256] = { 0 };


	};
}
