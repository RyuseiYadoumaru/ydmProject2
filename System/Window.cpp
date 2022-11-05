//*****************************************************************************
//* @file   Window.cpp
//* @brief  �E�B���h�E
//* @note   �A�v���P�[�V�����̃E�B���h�E���Ǘ�����
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
	// SJIS �� wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, string.c_str()
		, -1, (wchar_t*)NULL, 0);
	// �o�b�t�@�̎擾
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	// SJIS �� wstring
	MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, cpUCS2
		, iBufferSize);
	// string�̐���
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);
	// �o�b�t�@�̔j��
	delete[] cpUCS2;
	// �ϊ����ʂ�Ԃ�
	return(oRet);
}
#endif
#pragma endregion

//==============================================================================
//!	@fn		WindowProc
//!	@brief	�E�B���h�E�v���[�W���[
//!	@param	�E�B���h�E�n���h��
//!	@param	���b�Z�[�WID
//!	@param	���b�Z�[�W�p�����[�^
//!	@param	���b�Z�[�W�p�����[�^
//!	@retval	�I������ID
//==============================================================================
LRESULT APIENTRY WindowProc(HWND h_handle, UINT h_message, WPARAM h_wParam, LPARAM h_lParam)
{
	/****	�R�[���o�b�N�擾	****/
	WindowCallBack* callback = Window::GetInstance()->GetCallBack();
	if (callback == nullptr)
	{
		return DefWindowProc(h_handle, h_message, h_wParam, h_lParam);
	}
	/****	�R�[���o�b�N����	****/
	switch (h_message)
	{
		/****	�E�B���h�E�j��	****/
	case WM_DESTROY:
		return callback->OnDestroy(h_handle, h_message, h_wParam, h_lParam);
		break;

		/****	�V�X�e���L�[����	****/
	case WM_KEYDOWN:
		return callback->OnKeyDown(h_handle, h_message, h_wParam, h_lParam);
		break;

		/****	�E�B���h�E�I���I��	****/
	case WM_CLOSE:
		return callback->OnClose(h_handle, h_message, h_wParam, h_lParam);
		break;

		/****	�C�x���g�Ȃ�	****/
	default:
		return DefWindowProc(h_handle, h_message, h_wParam, h_lParam);
		break;
	}
	return 0;
}



//==============================================================================
//!	@fn		Create
//!	@brief	�E�B���h�E����
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Window::Create()
{
	auto app = Application::GetInstance();
	// �E�C���h�E��\������
	ShowWindow(m_handle, app->GetWindowMode());
	UpdateWindow(m_handle);

	return true;
}

//==============================================================================
//!	@fn		Close
//!	@brief	�E�B���h�E�N���[�Y
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Window::Close()
{
	DestroyWindow(m_handle);
	return true;
}


//==============================================================================
//!	@fn		ChangeWindowMode
//!	@brief	�E�B���h�E���[�h�ؑ�
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
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
//! @brief  �E�B���h�E���b�Z�[�W�e�L�X�g�ύX
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
//!	@brief	����������
//!	@note	�V���O���g���N���X�̏������𖾎��I�ɍs��
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Window::SetUp()
{
	/****	�G���[�`�F�b�N	****/
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

	/****	�E�B���h�E�N���X�o�^	****/
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

	/****	�E�B���h�E�T�C�Y	****/
	m_ResolutionList[Mode::Full_Screen] = DirectX::XMUINT2(1980, 1080);
	m_ResolutionList[Mode::Full_HD] = DirectX::XMUINT2(1980, 1080);
	m_ResolutionList[Mode::HD] = DirectX::XMUINT2(1280, 720);
	m_ResolutionList[Mode::VGA] = DirectX::XMUINT2(640, 480);
	m_ResolutionList[Mode::SVGA] = DirectX::XMUINT2(800, 600);
	m_ResolutionList[Mode::QVGA] = DirectX::XMUINT2(1280, 960);
	m_ResolutionList[Mode::UXGA] = DirectX::XMUINT2(1600, 1200);

	/****	�E�B���h�E�ݒ�	****/
	bool sts = SetWindow();
	if (sts == false)
	{
		return false;
	}

	// �R�[���o�b�N�֐��ݒ�
	m_CallBack = std::make_shared<WindowCallBack>();

	return true;
}

//==============================================================================
//!	@fn		ShutDown
//!	@brief	�I������
//!	@note	�V���O���g���N���X�̏I���𖾎��I�ɍs��
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Window::ShutDown()
{
	m_CallBack.reset();
	return true;
}

//==============================================================================
//!	@fn		SetWindow
//!	@brief	�E�B���h�E�ݒ�
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
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
			className.c_str(),			// �E�B���h�E�N���X�̖��O
			windowName.c_str(),				// �^�C�g��
			m_WindowStyleWindowed,				// �E�B���h�E�X�^�C��
			0, 0,								// �E�B���h�E�ʒu �c, ��
			width, height,						// �E�B���h�E�T�C�Y
			NULL,								// �e�E�B���h�E�Ȃ�
			(HMENU)NULL,						// ���j���[�Ȃ�
			app->GetHInstance(),				// �C���X�^���X�n���h��
			(LPVOID)NULL);						// �ǉ������Ȃ�
	}

	else
	{
		RECT	rWindow, rClient;

		m_handle = CreateWindowEx(
			m_WindowExStyleWindowed,
			className.c_str(),		// �E�B���h�E�N���X�̖��O
			windowName.c_str(),			// �^�C�g��
			WS_CAPTION | WS_SYSMENU,		// �E�B���h�E�X�^�C��
			0, 0,							// �E�B���h�E�ʒu �c, ��(���ƂŒ����Ɉړ������܂�)
			width, height,					// �E�B���h�E�T�C�Y
			HWND_DESKTOP,					// �e�E�B���h�E
			(HMENU)NULL,					// ���j���[�Ȃ�
			app->GetHInstance(),			// �C���X�^���X�n���h��
			(LPVOID)NULL);					// �ǉ������Ȃ�

		// �E�C���h�E�T�C�Y���Čv�Z
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