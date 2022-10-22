//*****************************************************************************
//* @file   Console.cpp
//* @brief  コンソールクラス
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
//!	@brief	初期化処理
//!	@note	シングルトンクラスの初期化を明示的に行う
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Console::SetUp()
{
#ifdef _DEBUG
	// コンソールを割り当てる
	AllocConsole();

	// 標準出力の割り当て
	freopen_s(&m_fp, "CON", "w", stdout);

	//ハンドル取得
	m_stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "========== System SetUp ==========" << std::endl;

#else
#endif // _DEBUG

	return true;
}

//==============================================================================
//!	@fn		ShutDown
//!	@brief	終了処理
//!	@note	シングルトンクラスの終了を明示的に行う
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Console::ShutDown()
{
#ifdef _DEBUG

	std::cout << "\n========== System ShutDown ==========" << std::endl;

	// 標準出力クローズ
	fclose(m_fp);

	// コンソール開放
	::FreeConsole();

#else
#endif // _DEBUG

	return true;
}


//==============================================================================
//!	@fn		SetTextColor
//!	@brief	テキストカラー設定
//==============================================================================
void systems::Console::TextColor(WORD color)
{
	WORD wAttributes;
	wAttributes = color;
	SetConsoleTextAttribute(m_stdOutHandle, wAttributes);
}
