//******************************************************************************
//* @file   Application.cpp
//* @brief  �A�v���P�[�V�����N���X
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
 *  �T�u�V�X�e���o�^.
 * 
 * !@param subSystem : �o�^�T�u�V�X�e���̃|�C���^
 * !@param errorText : �G���[���b�Z�[�W
 * !@return TRUE�@�����I��/ FALSE�@���s�I��
 */
bool Application::RegisterSubSystem(SubSystemPtr subSystem, String subsystemName)
{
	if (subSystem->SetUp() == false)
	{
		// �G���[���b�Z�[�W���o�͂���
		return false;
	}
	std::cout << "CreateSystem : " << subsystemName << std::endl;
	m_subSystems.push(subSystem);
	return true;
}


/**
 *  �A�v���P�[�V�����̃Z�b�g�A�b�v.
 * 
 * !@param h_instance : �C���X�^���X�n���h��
 * !@param windowMode : �E�B���h�E���[�h
 * !@return TRUE�@�����I��/ FALSE�@���s�I��
 */
bool Application::SetUp(HINSTANCE h_instance, int windowMode)
{
	/****	�A�v���P�[�V����������	****/
	m_hInstance	= h_instance;
	m_windowMode = windowMode;
	m_isSetUpComplete = true;

	/****	�V�X�e���o�^	****/
	RegisterSubSystem(Console::GetInstance(), "Console");
	RegisterSubSystem(Window::GetInstance(), "Window");
	RegisterSubSystem(SystemTimer::GetInstance(), "SystemTimer");
	RegisterSubSystem(DirectXGraphics::GetInstance(), "DX11");
	RegisterSubSystem(Inputsystem::GetInstance(), "InputSystem");
	RegisterSubSystem(AudioSystem::GetInstance(), "AudioSystem");
	RegisterSubSystem(GuiSystem::GetInstance(), "GuiSystem");

	/****	�E�B���h�E�\��	****/
	Window::GetInstance()->Create();

	//�����̕��������t�@�N�^����
	//DX11SetTransform::Get()->Init();
	return true;
}


/**============================================================================
//! @func   Run
//! @brief  �A�v���P�[�V�����X�V
//! @retval ���b�Z�[�W�R�}���h��Ԃ�
============================================================================*/
uInt16 Application::Run()
{
	//systems::MessageWindow* message = systems::MessageWindow::Instance();

	///** �Q�[�������� */
	//systems::GameSystem::Instance()->Initialaze();

	///** �Q�[���X�V */
	//while (message->ExecMessage() == true)
	//{
	//	systems::GameSystem::Instance()->Run();
	//}

	///** �Q�[���I������ */
	//systems::GameSystem::Instance()->Finalize();

	//return message->Message();
	return 0;
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
//!	@fn		SystemReleace
//!	@brief	�V�X�e�����
//==============================================================================
void Application::SystemReleace()
{
	while (m_subSystems.empty() == false)
	{
		// �T�u�V�X�e�������
		m_subSystems.front()->ShutDown();
		m_subSystems.pop();
	}
}
