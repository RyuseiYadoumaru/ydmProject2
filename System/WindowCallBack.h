//*****************************************************************************
//!	@file	WindowCallBack.h
//!	@brief	
//!	@note	�E�B���h�E�R�[���o�b�N�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#include	<Windows.h>

//=============================================================================
//!	@class	WindowCallBack
//!	@brief	�E�B���h�E�R�[���o�b�N
//=============================================================================
class WindowCallBack
{
public:

	LRESULT OnKeyDown(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
	LRESULT OnClose(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
	LRESULT OnWindowMove(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
	LRESULT OnDestroy(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam);
};



