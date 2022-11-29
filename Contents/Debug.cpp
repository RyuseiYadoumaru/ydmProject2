//*****************************************************************************
//* @file   Debug.cpp
//* @brief  デバッグクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include <iostream>
#include "Debug.h"
#include "../System/Console.h"


/****	デバックブレイク	****/
#ifdef  _DEBUG
#ifdef _M_IX86 ||_M_IX86FP
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
//!	@brief	ログ
//!	@note	コンソールに文字列を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::Log(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(LOG_COLOR);
	std::cout << log << std::endl;
}

//==============================================================================
//!	@fn		LogError
//!	@brief	ログエラー
//!	@note	コンソールにエラー文を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::LogError(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(ERROR_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	ログ警告
//!	@note	コンソールに警告文を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::LogWarning(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(WARNING_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		Stop
//!	@brief	処理をストップする
//==============================================================================
void tools::Debug::Stop()
{
	DEBUG_BREAK;
}


//==============================================================================
//!	@fn		Assert
//!	@brief	条件の時処理をストップする
//! //!	@param	flag : 条件式
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
//! @brief  条件の時処理をストップする
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
//!	@brief	ログ
//!	@note	コンソールに文字列を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::Log(String log)
{
}

//==============================================================================
//!	@fn		LogError
//!	@brief	ログエラー
//!	@note	コンソールにエラー文を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::LogError(String log)
{

}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	ログ警告
//!	@note	コンソールに警告文を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::LogWarning(String log)
{

}

//==============================================================================
//!	@fn		Stop
//!	@brief	処理をストップする
//==============================================================================
void tools::Debug::Stop()
{
}


//==============================================================================
//!	@fn		Assert
//!	@brief	条件の時処理をストップする
//! //!	@param	flag : 条件式
//==============================================================================
void tools::Debug::Assert(bool flag) noexcept
{
}


/**============================================================================
//! @func   Assert
//! @brief  条件の時処理をストップする
//! @param flag
//! @param log
============================================================================*/
void tools::Debug::Assert(bool flag, String log) noexcept
{
}


#endif // _DEBUG