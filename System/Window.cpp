//*****************************************************************************
//* @file   Window.cpp
//* @brief  ウィンドウ
//* @note   アプリケーションのウィンドウを管理する
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************

#include <Windows.h>
#include "Window.h"
#include "WindowCallback.h"
#include "Core/Application.h"
//#include "Tools/Debug.h"

using namespace systems;

Window::Mode		Window::m_WindowMode = Mode::HD;
String				Window::m_WindowName = "ydmProject";
String				Window::m_WindowClassName = "ydmProjectWindowClass";

const uInt32		Window::m_WindowStyleWindowed = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uInt32		Window::m_WindowExStyleWindowed = (0);
const uInt32		Window::m_WindowStyleFullScreen = (WS_VISIBLE | WS_POPUP);
const uInt32		Window::m_WindowExStyleFullScreen = (0);

Window::WindowSize	Window::m_ResolutionList(0);

#pragma region StringToWString
#ifdef _UNICODE
W_String StringToW_String(String string)
{
	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, string.c_str()
		, -1, (wchar_t*)NULL, 0);
	// バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	// SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, cpUCS2
		, iBufferSize);
	// stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);
	// バッファの破棄
	delete[] cpUCS2;
	// 変換結果を返す
	return(oRet);
}
#endif
#pragma endregion

//==============================================================================
//!	@fn		WindowProc
//!	@brief	ウィンドウプロージャー
//!	@param	ウィンドウハンドル
//!	@param	メッセージID
//!	@param	メッセージパラメータ
//!	@param	メッセージパラメータ
//!	@retval	終了結果ID
//==============================================================================
LRESULT APIENTRY WindowProc(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	/****	コールバック取得	****/
	WindowCallBack* callback = Window::GetInstance()->GetCallBack();
	if (callback == nullptr)
	{
		return DefWindowProc(h_handle, h_message, h_wParam, h_lParam);
	}
	/****	コールバック処理	****/
	switch (h_message)
	{
		/****	ウィンドウ破棄	****/
	case WM_DESTROY:
		return callback->OnDestroy(h_handle, h_message, h_wParam, h_lParam);
		break;

		/****	システムキー押下	****/
	case WM_KEYDOWN:
		return callback->OnKeyDown(h_handle, h_message, h_wParam, h_lParam);
		break;

		/****	ウィンドウ終了選択	****/
	case WM_CLOSE:
		return callback->OnClose(h_handle, h_message, h_wParam, h_lParam);
		break;

		/****	イベントなし	****/
	default:
		return DefWindowProc(h_handle, h_message, h_wParam, h_lParam);
		break;
	}
	return 0;
}



//==============================================================================
//!	@fn		Create
//!	@brief	ウィンドウ生成
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Window::Create()
{
	auto app = Application::GetInstance();
	// ウインドウを表示する
	ShowWindow(m_handle, app->GetWindowMode());
	UpdateWindow(m_handle);

	return true;
}

//==============================================================================
//!	@fn		Close
//!	@brief	ウィンドウクローズ
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Window::Close()
{
	DestroyWindow(m_handle);
	return true;
}


//==============================================================================
//!	@fn		ChangeWindowMode
//!	@brief	ウィンドウモード切替
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Window::ChangeMode(Mode windowMode)
{
	if (m_WindowMode == windowMode) return false;

	m_WindowMode = windowMode;
	SetWindow();

	return true;
}


/**============================================================================
//! @func   ChangeWindowText
//! @brief  ウィンドウメッセージテキスト変更
//! @param  message
============================================================================*/
void systems::Window::ChangeWindowText(String message) noexcept
{
#ifdef _UNICODE
	W_String w_message = StringToW_String(message);
	SetWindowText(m_handle, w_message.c_str());
#else
	SetWindowText(m_handle, message.c_str());
#endif // _UNICODE
}

//==============================================================================
//!	@fn		SetUp
//!	@brief	初期化処理
//!	@note	シングルトンクラスの初期化を明示的に行う
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Window::SetUp()
{
	/****	エラーチェック	****/
	if (Application::GetInstance()->SetUpComplete() == false)
	{
		//tools::Debug::LogError("Application SetUp Not Complete");
		return false;
	}
	auto app = Application::GetInstance();

#ifdef _UNICODE
	W_String className = StringToW_String(m_WindowClassName);
#else
	String className = m_WindowClassName;
#endif // _UNICODE

	/****	ウィンドウクラス登録	****/
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_OWNDC;
	WndClassEx.lpfnWndProc = WindowProc;
	WndClassEx.cbClsExtra = 0L;
	WndClassEx.cbWndExtra = 0L;
	WndClassEx.hInstance = app->GetHInstance();
	WndClassEx.hIcon = nullptr;
	WndClassEx.hCursor = nullptr;
	WndClassEx.hbrBackground = nullptr;
	WndClassEx.lpszMenuName = nullptr;
	WndClassEx.lpszClassName =className.c_str();
	WndClassEx.hIconSm = NULL;


	if (!RegisterClassEx(&WndClassEx))
	{
		//tools::Debug::LogError("RegisterClassEx");
		return false;
	}

	/****	ウィンドウサイズ	****/
	m_ResolutionList[Mode::Full_Screen] = DirectX::XMUINT2(1980, 1080);
	m_ResolutionList[Mode::Full_HD] = DirectX::XMUINT2(1980, 1080);
	m_ResolutionList[Mode::HD] = DirectX::XMUINT2(1280, 720);
	m_ResolutionList[Mode::VGA] = DirectX::XMUINT2(640, 480);
	m_ResolutionList[Mode::SVGA] = DirectX::XMUINT2(800, 600);
	m_ResolutionList[Mode::QVGA] = DirectX::XMUINT2(1280, 960);
	m_ResolutionList[Mode::UXGA] = DirectX::XMUINT2(1600, 1200);

	/****	ウィンドウ設定	****/
	bool sts = SetWindow();
	if (sts == false)
	{
		return false;
	}

	// コールバック関数設定
	m_CallBack = std::make_shared<WindowCallBack>();

	return true;
}

//==============================================================================
//!	@fn		ShutDown
//!	@brief	終了処理
//!	@note	シングルトンクラスの終了を明示的に行う
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Window::ShutDown()
{
	m_CallBack.reset();
	return true;
}

//==============================================================================
//!	@fn		SetWindow
//!	@brief	ウィンドウ設定
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Window::SetWindow()
{
	auto app = Application::GetInstance();

	uInt16 width = m_ResolutionList[m_WindowMode].x;
	uInt16 height = m_ResolutionList[m_WindowMode].y;

#ifdef _UNICODE
	W_String className = StringToW_String(m_WindowClassName);
	W_String windowName = StringToW_String(m_WindowName);
#else
	String className = m_WindowClassName;
	String windowName = m_WindowName;
#endif // _UNICODE


	if (m_WindowMode == Mode::Full_Screen)
	{
		m_handle = CreateWindowEx(
			m_WindowExStyleWindowed,
			className.c_str(),			// ウィンドウクラスの名前
			windowName.c_str(),				// タイトル
			m_WindowStyleWindowed,				// ウィンドウスタイル
			0, 0,								// ウィンドウ位置 縦, 横
			width, height,						// ウィンドウサイズ
			NULL,								// 親ウィンドウなし
			(HMENU)NULL,						// メニューなし
			app->GetHInstance(),				// インスタンスハンドル
			(LPVOID)NULL);						// 追加引数なし
	}

	else
	{
		RECT	rWindow, rClient;

		m_handle = CreateWindowEx(
			m_WindowExStyleWindowed,
			className.c_str(),		// ウィンドウクラスの名前
			windowName.c_str(),			// タイトル
			WS_CAPTION | WS_SYSMENU,		// ウィンドウスタイル
			0, 0,							// ウィンドウ位置 縦, 横(あとで中央に移動させます)
			width, height,					// ウィンドウサイズ
			HWND_DESKTOP,					// 親ウィンドウ
			(HMENU)NULL,					// メニューなし
			app->GetHInstance(),			// インスタンスハンドル
			(LPVOID)NULL);					// 追加引数なし

		// ウインドウサイズを再計算
		GetWindowRect(m_handle, &rWindow);
		GetClientRect(m_handle, &rClient);
		Int32 sizeWidth = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + width;
		Int32 sizeHeight = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + height;

		SetWindowPos(
			m_handle,
			NULL,
			GetSystemMetrics(SM_CXSCREEN) / 2 - sizeWidth / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - sizeHeight / 2,
			sizeWidth - 1,
			sizeHeight - 1,
			SWP_NOZORDER);
	}

	if (!m_handle)
	{
		MessageBox(nullptr, TEXT("CreateWindow Error"), TEXT("error"), MB_OK);
		return false;
	}

	m_screenSize.x = width;
	m_screenSize.y = height;
	return true;
}