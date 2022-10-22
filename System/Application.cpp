//******************************************************************************
//* @file   Application.cpp
//* @brief  �A�v���P�[�V�����N���X
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
//!	@brief	�A�v���P�[�V�����Z�b�g�A�b�v
//!	@note	�A�v���P�[�V�����̏����ݒ�
//!	@param	h_instance�F�C���X�^���X�n���h��
//!	@retval	TRUE�@�����I��/ FALSE�@���s�I��
//==============================================================================
bool Application::SetUp(HINSTANCE h_instance, int windowMode)
{
	/****	���������[�N���o	****/
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/****	�A�v���P�[�V����������	****/
	m_hInstance	= h_instance;
	m_windowMode = windowMode;
	m_isSetUpComplete = true;

	/****	�V�X�e������	****/
	if (SystemCreate() == false)
	{
		return false;
	}

	/****	�E�B���h�E�\��	****/
	systems::Window::Instance()->Create();


	//�����̕��������t�@�N�^����
	DX11SetTransform::Get()->Init();


	return true;
}


/**============================================================================
//! @func   Run
//! @brief  �A�v���P�[�V�����X�V
//! @retval ���b�Z�[�W�R�}���h��Ԃ�
============================================================================*/
uInt16 Application::Run()
{
	systems::MessageWindow* message = systems::MessageWindow::Instance();

	/** �Q�[�������� */
	systems::GameSystem::Instance()->Initialaze();

	/** �Q�[���X�V */
	while (message->ExecMessage() == true)
	{
		systems::GameSystem::Instance()->Run();
	}

	/** �Q�[���I������ */
	systems::GameSystem::Instance()->Finalize();

	return message->Message();
}


/**============================================================================
//! @func   ShutDown
//! @brief  �A�v���P�[�V�����I������
//! @retval TRUE�@�����I��/ FALSE�@���s�I��
============================================================================*/
bool Application::ShutDown()
{
	/****	�V�X�e�����	****/
	SystemReleace();

	return true;
}


//==============================================================================
//!	@fn		SystemCreate
//!	@brief	�V�X�e������
//==============================================================================
bool Application::SystemCreate()
{
	bool sts;
	sts = systems::Console::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("�R���\�[���̏������Ɏ��s");
	}
	
	sts = systems::SystemTimer::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("�V�X�e���^�C�}�[�̏������Ɏ��s");
		return false;
	}


	sts = systems::Window::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("Window�̏������Ɏ��s");
		return false;
	}
	
	sts = systems::Inputsystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("InputSystems�̏������Ɏ��s");
		return false;

	}

	sts = systems::DirectXGraphics::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("DirectXGraphics�̏������Ɏ��s");
		return false;
	}

	sts = systems::GuiSystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("GuiSystem�̏������Ɏ��s");
		return false;
	}

	systems::Soundsystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("�T�E���h�V�X�e���̏������Ɏ��s");
		return false;

	}


	sts = systems::GameSystem::Instance()->SetUp();
	if (sts == false)
	{
		systems::MessageWindow::Error("�Q�[���V�X�e���̏������Ɏ��s");
		return false;

	}

	return true;
}


//==============================================================================
//!	@fn		SystemReleace
//!	@brief	�V�X�e�����
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
