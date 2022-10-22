//*****************************************************************************
//* @file   MessageWindow.h
//* @brief  ���b�Z�[�W�E�B���h�E�N���X
//* @note   ���b�Z�[�W�E�B���h�E�̕\���A�Ǘ����s���B
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include "MessageWindow.h"
#include "Window.h"

//==============================================================================
//!	@fn		Error
//!	@brief	�G���[���b�Z�[�W
//!	@param	message�F�o�̓��b�Z�[�W
//==============================================================================
void systems::MessageWindow::Error(String message)
{
	HWND handle = Window::GetInstance()->GetHandle();
#ifdef _UNICODE
	W_String mes = (message == "") ? L"�G���[���������܂����B" : StringToW_String(message);
	W_String error = L"Error!";

#else
	String mes = (message == "") ? "" : message;
	String error = "Error!";
#endif // _UNICODE

	MessageBox(Window::GetInstance()->GetHandle(), mes.c_str(), error.c_str(), MB_OK);

}


//==============================================================================
//!	@fn		Error
//!	@brief	�I�����b�Z�[�W
//!	@param	message�F�o�̓��b�Z�[�W
//==============================================================================
int systems::MessageWindow::CloseWindow(String message)
{
	HWND handle = Window::GetInstance()->GetHandle();
#ifdef _UNICODE
	W_String mes = (message == "") ? L"�A�v���P�[�V�������I�����܂����H" : StringToW_String(message);
	W_String close = L"CloseWindow?";

#else
	String mes = (message == "") ? "�A�v���P�[�V�������I�����܂����H" : message;
	String close = "CloseWindow?";
#endif // _UNICODE
	return MessageBox(handle, mes.c_str(), close.c_str(), MB_YESNO);
}


//==============================================================================
//!	@fn		Warning
//!	@brief	�x�����b�Z�[�W
//!	@param	message�F�o�̓��b�Z�[�W
//==============================================================================
int systems::MessageWindow::Warning(String message)
{
	HWND handle = Window::GetInstance()->GetHandle();
#ifdef _UNICODE
	W_String mes = (message == "") ? L"�ُ�ȏ������s���Ă��܂��B" : StringToW_String(message);
	W_String warning = L"Warning!";

#else
	String mes = (message == "") ? "�ُ�ȏ������s���Ă��܂��B" : message;
	String warning = "Warning!";
#endif // _UNICODE
	return MessageBox(handle, mes.c_str(), warning.c_str(), MB_ABORTRETRYIGNORE);
}


//==============================================================================
//!	@fn		ExecMessage
//!	@brief	���b�Z�[�W����
//!	@retval	TRUE�@�p���@/FALSE�@�I��
//==============================================================================
bool systems::MessageWindow::ExecMessage()
{
	while (PeekMessage(&m_windowMessage, NULL, 0, 0, PM_NOREMOVE))
	{
		// ���b�Z�[�W�Ȃ�
		if (GetMessage(&m_windowMessage, NULL, 0, 0) == false) return false;
		TranslateMessage(&m_windowMessage);		// �L�[���b�Z�[�W�ϊ�
		DispatchMessage(&m_windowMessage);		// ���b�Z�[�W���o
	}

	return true;
}
