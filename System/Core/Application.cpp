//******************************************************************************
//* @file   Application.cpp
//* @brief  アプリケーションクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include "Application.h"
#include "../Audiosystem.h"
#include "../Console.h"
#include "../DirectXGraphics.h"
#include "../GameSystem.h"
#include "../GuiSystem.h"
#include "../MessageWindow.h"
#include "../Inputsystem.h"
#include "../SystemTimer.h"
#include "../Window.h"

#include "../DX11Renderer.h"

#include "Debug.h"


USING_SYSTEMS;
USING_TOOLS;

/**
 *  サブシステム登録.
 * 
 * !@param subSystem : 登録サブシステムのポインタ
 * !@param errorText : エラーメッセージ
 * !@return TRUE　成功終了/ FALSE　失敗終了
 */
bool Application::RegisterSubSystem(SubSystemPtr subSystem, String subsystemName)
{
	if (subSystem->SetUp() == false)
	{
		// エラーメッセージを出力する
		return false;
	}
	Debug::Log("CreateSystem : ", subsystemName);
	m_subSystems.push(subSystem);
	return true;
}


/**
 *  アプリケーションのセットアップ.
 * 
 * !@param h_instance : インスタンスハンドル
 * !@param windowMode : ウィンドウモード
 * !@return TRUE　成功終了/ FALSE　失敗終了
 */
bool Application::SetUp(HINSTANCE h_instance, int windowMode)
{
	/****	アプリケーション初期化	****/
	m_hInstance	= h_instance;
	m_windowMode = windowMode;
	m_isSetUpComplete = true;

	/****	システム登録	****/
	RegisterSubSystem(Console::GetInstance(), "Console");
	RegisterSubSystem(Window::GetInstance(), "Window");
	RegisterSubSystem(SystemTimer::GetInstance(), "SystemTimer");
	RegisterSubSystem(DirectXGraphics::GetInstance(), "DX11");
	RegisterSubSystem(Inputsystem::GetInstance(), "InputSystem");
	RegisterSubSystem(AudioSystem::GetInstance(), "AudioSystem");
	RegisterSubSystem(GuiSystem::GetInstance(), "GuiSystem");
	RegisterSubSystem(GameSystem::GetInstance(), "GameSystem");

	/****	ウィンドウ表示	****/
	Window::GetInstance()->Create();

	return true;
}


/**============================================================================
//! @func   Run
//! @brief  アプリケーション更新
//! @retval メッセージコマンドを返す
============================================================================*/
uInt16 Application::Run()
{
	auto game = GameSystem::GetInstance();
	auto gui = GuiSystem::GetInstance();
	auto message = MessageWindow::GetInstance();
	auto renderManager = DX11Renderer::GetInstance();

	///** ゲーム初期化 */
	game->GameSystemStart();
	gui->EditorSetUp();

	/** ゲーム更新 */
	while (message->ExecMessage() == true)
	{
		renderManager->ClearRenderer();
		game->Run();
		gui->Run();
		renderManager->SwapRenderBuffer();
	}

	///** ゲーム終了処理 */
	game->GameSystemEnd();
	return message->Message();
}

/**============================================================================
//! @func   ShutDown
//! @brief  アプリケーション終了処理
//! @retval TRUE　成功終了/ FALSE　失敗終了
============================================================================*/
bool Application::ShutDown()
{
	/****	システム解放	****/
	SystemReleace();

	return true;
}


//==============================================================================
//!	@fn		SystemReleace
//!	@brief	システム解放
//==============================================================================
void Application::SystemReleace()
{
	while (m_subSystems.empty() == false)
	{
		m_subSystems.front()->ShutDown();
		m_subSystems.pop();
	}
}
