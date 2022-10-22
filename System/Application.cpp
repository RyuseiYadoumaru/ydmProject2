//******************************************************************************
//* @file   Application.cpp
//* @brief  アプリケーションクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************

#include "Application.h"
#include "../Window/Window.h"
#include "../Message/MessageWindow.h"
#include "../Console/Console.h"
#include "../Timer/SystemTimer.h"
#include "../GameSystem/GameSystem.h"
#include "../Systems/Core/Graphics/DirectXGraphics.h"
#include "../Input/Inputsystem.h"
#include "../Sound/Soundsystem.h"
#include "../Gui/GuiSystem.h"
//#include "../../dx11util.h"
#include "../Systems/Core/Renderer/ConstentBuffer/DX11Settransform.h"
//#include "Config.h"

//==============================================================================
//!	@fn		SetUp
//!	@brief	アプリケーションセットアップ
//!	@note	アプリケーションの初期設定
//!	@param	h_instance：インスタンスハンドル
//!	@retval	TRUE　成功終了/ FALSE　失敗終了
//==============================================================================
bool Application::SetUp(HINSTANCE h_instance, int windowMode)
{
	/****	メモリリーク検出	****/
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/****	アプリケーション初期化	****/
	m_hInstance	= h_instance;
	m_windowMode = windowMode;
	m_isSetUpComplete = true;

	/****	システム生成	****/
	if (SystemCreate() == false)
	{
		return false;
	}

	/****	ウィンドウ表示	****/
	systems::Window::Instance()->Create();


	//ここの部分もリファクタする
	DX11SetTransform::Get()->Init();


	return true;
}


/**============================================================================
//! @func   Run
//! @brief  アプリケーション更新
//! @retval メッセージコマンドを返す
============================================================================*/
uInt16 Application::Run()
{
	systems::MessageWindow* message = systems::MessageWindow::Instance();

	/** ゲーム初期化 */
	systems::GameSystem::Instance()->Initialaze();

	/** ゲーム更新 */
	while (message->ExecMessage() == true)
	{
		systems::GameSystem::Instance()->Run();
	}

	/** ゲーム終了処理 */
	systems::GameSystem::Instance()->Finalize();

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
//!	@fn		SystemCreate
//!	@brief	システム生成
//==============================================================================
bool Application::SystemCreate()
{
	bool sts;
	sts = systems::Console::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("コンソールの初期化に失敗");
	}
	
	sts = systems::SystemTimer::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("システムタイマーの初期化に失敗");
		return false;
	}


	sts = systems::Window::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("Windowの初期化に失敗");
		return false;
	}
	
	sts = systems::Inputsystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("InputSystemsの初期化に失敗");
		return false;

	}

	sts = systems::DirectXGraphics::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("DirectXGraphicsの初期化に失敗");
		return false;
	}

	sts = systems::GuiSystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("GuiSystemの初期化に失敗");
		return false;
	}

	systems::Soundsystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("サウンドシステムの初期化に失敗");
		return false;

	}


	sts = systems::GameSystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("ゲームシステムの初期化に失敗");
		return false;

	}

	return true;
}


//==============================================================================
//!	@fn		SystemReleace
//!	@brief	システム解放
//==============================================================================
void Application::SystemReleace()
{
	systems::GameSystem::Instance()->ShutDown();
	systems::Soundsystem::Instance()->ShutDown();
	systems::GuiSystem::Instance()->ShutDown();
	systems::DirectXGraphics::Instance()->ShutDown();
	systems::Inputsystem::Instance()->ShutDown();
	systems::Window::Instance()->ShutDown();
	systems::SystemTimer::Instance()->ShutDown();
	systems::Console::Instance()->ShutDown();

}
