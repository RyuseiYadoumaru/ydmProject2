//*****************************************************************************
//* @file   Window.h
//* @brief  ウィンドウ
//* @note   アプリケーションのウィンドウを管理する
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include "SubSystem.h"
#include "macro.h"
#include "std.h"
class WindowCallBack;

#ifdef  _UNICODE
W_String StringToW_String(String string);
#endif //  _UNICODE


namespace systems
{

	class Window final : public SubSystem
	{
		SINGLETON_CLASS(Window);
	public:
		enum class Mode
		{
			Full_Screen,
			Full_HD,
			HD,

			VGA,
			SVGA,
			QVGA,
			UXGA
		};
	using WindowSize = Unordered_Map<Mode, DirectX::XMUINT2>;

	public:
		bool Create();
		bool Close();
		bool ChangeMode(Mode windowMode);
		void ChangeWindowText(String message) noexcept;

		bool SetUp() override;
		bool ShutDown() override;

		HWND GetHandle() const noexcept { return m_handle; }
		WindowCallBack* GetCallBack() const noexcept { return m_CallBack.get(); }
		const DirectX::XMUINT2& GetScreenSize() const noexcept { return m_screenSize; }
		const Mode& GetWindowMode() const noexcept { return m_WindowMode; }

		String GetWindowClassName() const noexcept { return m_WindowClassName; }

	private:
		static Mode	m_WindowMode;
		static String		m_WindowName;
		static String		m_WindowClassName;

		static const uInt32		m_WindowStyleWindowed;
		static const uInt32		m_WindowExStyleWindowed;
		static const uInt32		m_WindowStyleFullScreen;
		static const uInt32		m_WindowExStyleFullScreen;

		static WindowSize m_ResolutionList;

	private:
		DirectX::XMUINT2	m_screenSize = { 0, 0 };

	private:
		bool SetWindow();

	private:
		HWND							m_handle = NULL;
		SharedPtr<WindowCallBack>		m_CallBack;

	};
}