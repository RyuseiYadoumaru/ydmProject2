//*****************************************************************************
//!	@file	WindowCallBack.cpp
//!	@brief	
//!	@note	ウィンドウコールバッククラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "WindowCallBack.h"
#include "Application.h"

//==============================================================================
//!	@fn		OnKeyDown
//!	@brief	キー押下
//!	@param	
//!	@retval	終了結果
//==============================================================================
LRESULT WindowCallBack::OnKeyDown(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	return 0;
}

//==============================================================================
//!	@fn		OnClose
//!	@brief　×
//!	@param	
//!	@retval	終了結果
//==============================================================================
LRESULT WindowCallBack::OnClose(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	//int status = Log::LogCloseWindow(h_Handle, "終了しますか？");
	//if (status == IDYES)
	//{
	//	return DestroyWindow(h_Handle);
	//}
	PostQuitMessage(0);

	return 0;
}

//==============================================================================
//!	@fn		OnWindowMove
//!	@brief　ウィンドウ移動中
//!	@param	
//!	@retval	終了結果
//==============================================================================
LRESULT WindowCallBack::OnWindowMove(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	return 0;
}

//==============================================================================
//!	@fn		OnDestroy
//!	@brief　終了
//!	@param	
//!	@retval 0
//==============================================================================
LRESULT WindowCallBack::OnDestroy(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	PostQuitMessage(0);
	return 0;
}
//******************************************************************************
//	End of file.
//******************************************************************************
