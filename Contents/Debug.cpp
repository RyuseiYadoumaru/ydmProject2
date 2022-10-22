//*****************************************************************************
//* @file   Debug.cpp
//* @brief  �f�o�b�O�N���X
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include <iostream>
#include "Debug.h"
#include "../System/Console.h"


/****	�f�o�b�N�u���C�N	****/
#ifdef  _DEBUG
#ifdef _M_IX86 || _M_IX86FP
#define DEBUG_BREAK _asm{ int 3 }
#else
#define DEBUG_BREAK __debugbreak()
#endif // _M_IX86 || _M_IX86FP
#else
#define DEBUG_BREAK
#endif //  _DEBUG

#define LOG_COLOR		(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define ERROR_COLOR		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define WARNING_COLOR	(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


#ifdef  _DEBUG
//==============================================================================
//!	@fn		Log
//!	@brief	���O
//!	@note	�R���\�[���ɕ�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::Log(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(LOG_COLOR);
	std::cout << log << std::endl;
}

//==============================================================================
//!	@fn		LogError
//!	@brief	���O�G���[
//!	@note	�R���\�[���ɃG���[�����o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogError(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(ERROR_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	���O�x��
//!	@note	�R���\�[���Ɍx�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogWarning(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(WARNING_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		Stop
//!	@brief	�������X�g�b�v����
//==============================================================================
void tools::Debug::Stop()
{
	DEBUG_BREAK;
}


//==============================================================================
//!	@fn		Assert
//!	@brief	�����̎��������X�g�b�v����
//! //!	@param	flag : ������
//==============================================================================
void tools::Debug::Assert(bool flag) noexcept
{
	if (flag == false) return;
	else
	{
		DEBUG_BREAK;
	}
}


/**============================================================================
//! @func   Assert
//! @brief  �����̎��������X�g�b�v����
//! @param flag
//! @param log
============================================================================*/
void tools::Debug::Assert(bool flag, String log) noexcept
{
	if (flag == false) return;
	else
	{
		LogError(log);
		DEBUG_BREAK;
	}
}


#else
//==============================================================================
//!	@fn		Log
//!	@brief	���O
//!	@note	�R���\�[���ɕ�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::Log(String log)
{
	//�����[�X���̏���������
}

//==============================================================================
//!	@fn		LogError
//!	@brief	���O�G���[
//!	@note	�R���\�[���ɃG���[�����o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogError(String log)
{
	//�����[�X���̏���������
}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	���O�x��
//!	@note	�R���\�[���Ɍx�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogWarning(String log)
{
	//�����[�X���̏���������
}


#endif // _DEBUG