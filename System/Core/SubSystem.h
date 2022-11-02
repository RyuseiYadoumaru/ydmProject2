//*****************************************************************************
//* @file   SubSystem.h
//* @brief  �T�u�V�X�e��
//* @note   �A�v���P�[�V�����ɕt������V�X�e���̊��N���X
//* 
//* @author YadoumaruRyusei
//* @date   October 2022
//*****************************************************************************
#pragma once
#include "std.h"

namespace systems
{
	class SubSystem
	{
	public:
		virtual bool SetUp()	= 0;
		virtual bool ShutDown() = 0;
	};
}
