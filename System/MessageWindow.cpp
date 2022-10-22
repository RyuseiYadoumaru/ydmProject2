//*****************************************************************************
//* @file   MessageWindow.h
//* @brief  メッセージウィンドウクラス
//* @note   メッセージウィンドウの表示、管理を行う。
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include "MessageWindow.h"
#include "Window.h"

//==============================================================================
//!	@fn		Error
//!	@brief	エラーメッセージ
//!	@param	message：出力メッセージ
//==============================================================================
void systems::MessageWindow::Error(String message)
{
	HWND handle = Window::GetInstance()->GetHandle();
#ifdef _UNICODE
	W_String mes = (message == "") ? L"エラーが発生しました。" : StringToW_String(message);
	W_String error = L"Error!";

#else
	String mes = (message == "") ? "" : message;
	String error = "Error!";
#endif // _UNICODE

	MessageBox(Window::GetInstance()->GetHandle(), mes.c_str(), error.c_str(), MB_OK);

}


//==============================================================================
//!	@fn		Error
//!	@brief	終了メッセージ
//!	@param	message：出力メッセージ
//==============================================================================
int systems::MessageWindow::CloseWindow(String message)
{
	HWND handle = Window::GetInstance()->GetHandle();
#ifdef _UNICODE
	W_String mes = (message == "") ? L"アプリケーションを終了しますか？" : StringToW_String(message);
	W_String close = L"CloseWindow?";

#else
	String mes = (message == "") ? "アプリケーションを終了しますか？" : message;
	String close = "CloseWindow?";
#endif // _UNICODE
	return MessageBox(handle, mes.c_str(), close.c_str(), MB_YESNO);
}


//==============================================================================
//!	@fn		Warning
//!	@brief	警告メッセージ
//!	@param	message：出力メッセージ
//==============================================================================
int systems::MessageWindow::Warning(String message)
{
	HWND handle = Window::GetInstance()->GetHandle();
#ifdef _UNICODE
	W_String mes = (message == "") ? L"異常な処理が行われています。" : StringToW_String(message);
	W_String warning = L"Warning!";

#else
	String mes = (message == "") ? "異常な処理が行われています。" : message;
	String warning = "Warning!";
#endif // _UNICODE
	return MessageBox(handle, mes.c_str(), warning.c_str(), MB_ABORTRETRYIGNORE);
}


//==============================================================================
//!	@fn		ExecMessage
//!	@brief	メッセージ処理
//!	@retval	TRUE　継続　/FALSE　終了
//==============================================================================
bool systems::MessageWindow::ExecMessage()
{
	while (PeekMessage(&m_windowMessage, NULL, 0, 0, PM_NOREMOVE))
	{
		// メッセージなし
		if (GetMessage(&m_windowMessage, NULL, 0, 0) == false) return false;
		TranslateMessage(&m_windowMessage);		// キーメッセージ変換
		DispatchMessage(&m_windowMessage);		// メッセージ送出
	}

	return true;
}
