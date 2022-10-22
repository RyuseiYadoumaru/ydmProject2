//******************************************************************************
//* @file   Application.cpp
//* @brief  アプリケーションクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************

#include <iostream>
#include "Application.h"
#include "Console.h"
#include "Window.h"
#include "MessageWindow.h"
#include "SystemTimer.h"
#include "Inputsystem.h"
#include "DirectXGraphics.h"
#include "Audiosystem.h"
//#include "../GameSystem/GameSystem.h"
#include "GuiSystem.h"
//#include "../../dx11util.h"
//#include "../Systems/Core/Renderer/ConstentBuffer/DX11Settransform.h"
//#include "Config.h"

USING_SYSTEMS;

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
	std::cout << "CreateSystem : " << subsystemName << std::endl;
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

	/****	ウィンドウ表示	****/
	Window::GetInstance()->Create();

	//ここの部分もリファクタする
	//DX11SetTransform::Get()->Init();
	return true;
}


/**============================================================================
//! @func   Run
//! @brief  アプリケーション更新
//! @retval メッセージコマンドを返す
============================================================================*/
uInt16 Application::Run()
{
	//systems::MessageWindow* message = systems::MessageWindow::Instance();

	///** ゲーム初期化 */
	//systems::GameSystem::Instance()->Initialaze();

	///** ゲーム更新 */
	//while (message->ExecMessage() == true)
	//{
	//	systems::GameSystem::Instance()->Run();
	//}

	///** ゲーム終了処理 */
	//systems::GameSystem::Instance()->Finalize();

	//return message->Message();
	return 0;
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
		// サブシステムを解放
		m_subSystems.front()->ShutDown();
		m_subSystems.pop();
	}
}
