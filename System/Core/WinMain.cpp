

//*****************************************************************************
//* @file   WinMain.cpp
//* @brief  
//* @note   アプリケーション開始
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************

#include "../ThirdParty/LibraryHeader.h"
#include <Windows.h>
#include "Application.h"

/**============================================================================
//! @func   WinMain
//! @brief  エントリポイント
//! @param h_hInst
//! @param h_hPrevInst
//! @param h_lpszArgs
//! @param h_nWinMode
//! @retval 
============================================================================*/
INT WINAPI WinMain(HINSTANCE  h_hInst, HINSTANCE h_hPrevInst, LPSTR h_lpszArgs, int h_nWinMode)
{
	auto app = systems::Application::GetInstance();
	uInt32 windowMessage = 0;
	if (app->SetUp(h_hInst, h_nWinMode) == true)
	{
		windowMessage = app->Run();
	}
	app->ShutDown();
	return windowMessage;
}
