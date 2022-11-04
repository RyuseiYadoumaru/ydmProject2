//******************************************************************************
//* @file   Keyboard.h
//* @brief  �L�[�{�[�h
//* @note   �L�[�{�[�h���͂��Ǘ�����
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
		 * �L�[�{�[�h�v���X����.
		 */
		static bool Press(Keycode input);
		
		/**
		 * �L�[�{�[�h�����[�X����.
		 * ���݂̓g���K�[�̏����ɂȂ��Ă���.
		 */
		static bool Releace(Keycode input);
		
		
		/**
		 * �L�[�{�[�h�g���K�[����
		 */
		static bool Trigger(Keycode input);
	};

}
