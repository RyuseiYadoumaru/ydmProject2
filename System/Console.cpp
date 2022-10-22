//*****************************************************************************
//* @file   Console.cpp
//* @brief  �R���\�[���N���X
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include <Crtdbg.h>
#include <Windows.h>
#include <iostream>
#include "Console.h"


//==============================================================================
//!	@fn		SetUp
//!	@brief	����������
//!	@note	�V���O���g���N���X�̏������𖾎��I�ɍs��
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Console::SetUp()
{
#ifdef _DEBUG
	// �R���\�[�������蓖�Ă�
	AllocConsole();

	// �W���o�͂̊��蓖��
	freopen_s(&m_fp, "CON", "w", stdout);

	//�n���h���擾
	m_stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "========== System SetUp ==========" << std::endl;

#else
#endif // _DEBUG

	return true;
}

//==============================================================================
//!	@fn		ShutDown
//!	@brief	�I������
//!	@note	�V���O���g���N���X�̏I���𖾎��I�ɍs��
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Console::ShutDown()
{
#ifdef _DEBUG

	std::cout << "\n========== System ShutDown ==========" << std::endl;

	// �W���o�̓N���[�Y
	fclose(m_fp);

	// �R���\�[���J��
	::FreeConsole();

#else
#endif // _DEBUG

	return true;
}


//==============================================================================
//!	@fn		SetTextColor
//!	@brief	�e�L�X�g�J���[�ݒ�
//==============================================================================
void systems::Console::TextColor(WORD color)
{
	WORD wAttributes;
	wAttributes = color;
	SetConsoleTextAttribute(m_stdOutHandle, wAttributes);
}
