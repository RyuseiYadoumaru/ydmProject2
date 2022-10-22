//*****************************************************************************
//!	@file	WindowCallBack.h
//!	@brief	
//!	@note	ウィンドウコールバッククラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#include	<Windows.h>

//=============================================================================
//!	@class	WindowCallBack
//!	@brief	ウィンドウコールバック
//=============================================================================
class WindowCallBack
{
public:

	LRESULT OnKeyDown(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
	LRESULT OnClose(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
	LRESULT OnWindowMove(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
	LRESULT OnDestroy(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
};



