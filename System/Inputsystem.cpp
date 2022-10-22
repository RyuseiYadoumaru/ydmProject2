//*****************************************************************************
//* @file   Inputsystem.cpp
//* @brief  インプットシステム
//* @note   入力系のセットアップを行う
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include "Inputsystem.h"
#include "Application.h"
#include "Window.h"
#include "Debug.h"


//==============================================================================
//!	@fn		SetUp
//!	@brief	初期化
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Inputsystem::SetUp()
{
	/**
	 * 入力全般初期化.
	 */	
	HRESULT hr;
	auto app = Application::GetInstance();

	hr = DirectInput8Create(
		app->GetHInstance(),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_directInput,
		NULL);

	if (FAILED(hr))
	{
		tools::Debug::LogError("インプットシステム初期化に失敗");
		return false;
	}

	/**
	 * キーボード初期化.
	 */
	// キーボードデバイス生成
	hr = m_directInput.Get()->CreateDevice(GUID_SysKeyboard, &m_directKeyboard, NULL);
	if (FAILED(hr))
	{
		tools::Debug::LogError("キーボード初期化に失敗");
		return false;
	}

	// データフォーマット設定
	m_directKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// 協調レベル設定
	Window* window = Window::GetInstance();
	m_directKeyboard->SetCooperativeLevel(window->GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	/**
	 * マウス初期化.
	 */
	// マウスデバイス生成
	hr = m_directInput.Get()->CreateDevice(GUID_SysMouse, &m_directMouse, NULL);
	if (FAILED(hr))
	{
		tools::Debug::LogError("マウスの初期化に失敗");
		return false;
	}

	// データフォーマットを設定
	hr = m_directMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		tools::Debug::LogError("マウスのフォーマットの設定に失敗");
		return false;
	}

	// 協調モード設定
	// フォアグランドと非排他モードに設定しています
	hr = m_directMouse->SetCooperativeLevel(window->GetHandle(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		tools::Debug::LogError("マウス協調モード設定に失敗");
		return false;
	}

	// 入力デバイスの制御を開始する
	m_directKeyboard->Acquire();
	m_directMouse->Acquire();

	// デバイスのポーリングを開始する
	// 一定間隔でデバイスの情報を同期させて取得します
	// これによって競合の回避や処理の動機にを行います
	hr = m_directKeyboard->Poll();
	if (FAILED(hr))
	{
		tools::Debug::LogError("キーデバイスのポーリングに失敗しました。");
		return false;
	}

	hr = m_directMouse->Poll();
	if (FAILED(hr))
	{
		tools::Debug::LogError("マウスデバイスのポーリングに失敗しました。");
		return false;
	}
	return true;
}


//==============================================================================
//!	@fn		ShutDown
//!	@brief	終了処理
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::Inputsystem::ShutDown()
{
	// 入力デバイスの制御を停止する
	m_directKeyboard->Unacquire();
	m_directMouse->Unacquire();

	// IDirectInput8の解放を行う
	m_directInput->Release();
	m_directKeyboard->Release();
	m_directMouse->Release();

	m_directMouse.Reset();
	m_directKeyboard.Reset();
	m_directInput.Reset();
	return true;
}