//*****************************************************************************
//* @file   ManagerInterface.h
//* @brief  �}�l�[�W���[�֘A�̃C���^�[�t�F�[�X
//* @note   �e�}�l�[�W���[�̃t�����h�ɂȂ�܂�
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class ManagerInterface
	{
	public:
		static void SetUp();
		static void ShutDown();
	};
}
