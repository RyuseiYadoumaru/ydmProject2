//*****************************************************************************
//* @file   MessageWindow.h
//* @brief  メッセージウィンドウクラス
//* @note   メッセージウィンドウの表示、管理を行う。
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include <Windows.h>
#include "std.h"
#include "macro.h"

namespace systems
{
	class MessageWindow final
	{
		SINGLETON_CLASS(MessageWindow);
	public:
		static void Error(String message = "");
		static int CloseWindow(String message = "");
		static int Warning(String message = "");
		bool ExecMessage();

	public:
		const uInt16 Message() const { return m_windowMessage.message; }

	private:
		HWND	m_windowHandle;
		MSG		m_windowMessage;
	};
};
