//*****************************************************************************
//!	@file	WindowCallBack.cpp
//!	@brief	
//!	@note	�E�B���h�E�R�[���o�b�N�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "WindowCallBack.h"
#include "Application.h"

//==============================================================================
//!	@fn		OnKeyDown
//!	@brief	�L�[����
//!	@param	
//!	@retval	�I������
//==============================================================================
LRESULT WindowCallBack::OnKeyDown(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	return 0;
}

//==============================================================================
//!	@fn		OnClose
//!	@brief�@�~
//!	@param	
//!	@retval	�I������
//==============================================================================
LRESULT WindowCallBack::OnClose(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	//int status = Log::LogCloseWindow(h_Handle, "�I�����܂����H");
	//if (status == IDYES)
	//{
	//	return DestroyWindow(h_Handle);
	//}
	PostQuitMessage(0);

	return 0;
}

//==============================================================================
//!	@fn		OnWindowMove
//!	@brief�@�E�B���h�E�ړ���
//!	@param	
//!	@retval	�I������
//==============================================================================
LRESULT WindowCallBack::OnWindowMove(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	return 0;
}

//==============================================================================
//!	@fn		OnDestroy
//!	@brief�@�I��
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
