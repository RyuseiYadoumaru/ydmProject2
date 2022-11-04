//*****************************************************************************
//* @file   MouseSystem.h
//* @brief  �}�E�X�V�X�e��
//* @note   �}�E�X���͎���̍X�V���s��
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************
#pragma once
#include <dinput.h>
#include "GameSubSysmte.h"
#include "macro.h"
#include "std.h"

namespace GAME_SYSTEMS
{
	class MouseSystem : public GameSubSystem
	{
		GAMESUBSYSTEM;

	public:
		DIMOUSESTATE& GetMouseState() noexcept { return m_mouseState; }
		DIMOUSESTATE& GetOldMouseState() noexcept { return m_oldMouseState; }

		bool Initialize() override;
		bool Run() override;
		bool Finalize() override;

	public:
		constexpr static Byte m_MaskInputMouseBuffer = 0x80;

	private:
		DIMOUSESTATE m_mouseState;		// �}�E�X���
		DIMOUSESTATE m_oldMouseState;	// �O�t���[���̃}�E�X���

	};
}
