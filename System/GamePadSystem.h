//*****************************************************************************
//* @file   GamePadSystem.h
//* @brief  �Q�[���p�b�h�V�X�e��
//* @note   �Q�[���p�b�h�̓��͎���̍X�V���s��
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once


#include "Inputsystem.h"
#include "GameSubSysmte.h"
#include "macro.h"
#include "std.h"

#include <xinput.h>
#pragma comment (lib, "xinput.lib")

namespace GAME_SYSTEMS
{
	class GamePadSystem : public GameSubSystem
	{
		GAMESUBSYSTEM;

	public:
		XINPUT_STATE& GetXinputState(uInt32 index = 0) noexcept { return m_xinputState[index]; }
		XINPUT_STATE& GetOldXinputState(uInt32 index = 0) noexcept { return m_oldXinputState[index]; }

	public:
		bool Initialize() override;
		bool Run() override;
		bool Finalize() override;

	private:
		constexpr static uInt32 m_gamePadMaxNum = 4;

	private:
		Array<XINPUT_STATE, m_gamePadMaxNum> m_xinputState;			// �Q�[���p�b�h�X�e�[�^�X
		Array<XINPUT_STATE, m_gamePadMaxNum> m_oldXinputState;		// �O�t���[���̃X�e�[�^�X

	};
}
