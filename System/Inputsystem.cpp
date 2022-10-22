//*****************************************************************************
//* @file   Inputsystem.cpp
//* @brief  �C���v�b�g�V�X�e��
//* @note   ���͌n�̃Z�b�g�A�b�v���s��
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
//!	@brief	������
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Inputsystem::SetUp()
{
	/**
	 * ���͑S�ʏ�����.
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
		tools::Debug::LogError("�C���v�b�g�V�X�e���������Ɏ��s");
		return false;
	}

	/**
	 * �L�[�{�[�h������.
	 */
	// �L�[�{�[�h�f�o�C�X����
	hr = m_directInput.Get()->CreateDevice(GUID_SysKeyboard, &m_directKeyboard, NULL);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�L�[�{�[�h�������Ɏ��s");
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�ݒ�
	m_directKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// �������x���ݒ�
	Window* window = Window::GetInstance();
	m_directKeyboard->SetCooperativeLevel(window->GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	/**
	 * �}�E�X������.
	 */
	// �}�E�X�f�o�C�X����
	hr = m_directInput.Get()->CreateDevice(GUID_SysMouse, &m_directMouse, NULL);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�}�E�X�̏������Ɏ��s");
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_directMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�}�E�X�̃t�H�[�}�b�g�̐ݒ�Ɏ��s");
		return false;
	}

	// �������[�h�ݒ�
	// �t�H�A�O�����h�Ɣ�r�����[�h�ɐݒ肵�Ă��܂�
	hr = m_directMouse->SetCooperativeLevel(window->GetHandle(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		tools::Debug::LogError("�}�E�X�������[�h�ݒ�Ɏ��s");
		return false;
	}

	// ���̓f�o�C�X�̐�����J�n����
	m_directKeyboard->Acquire();
	m_directMouse->Acquire();

	// �f�o�C�X�̃|�[�����O���J�n����
	// ���Ԋu�Ńf�o�C�X�̏��𓯊������Ď擾���܂�
	// ����ɂ���ċ����̉���⏈���̓��@�ɂ��s���܂�
	hr = m_directKeyboard->Poll();
	if (FAILED(hr))
	{
		tools::Debug::LogError("�L�[�f�o�C�X�̃|�[�����O�Ɏ��s���܂����B");
		return false;
	}

	hr = m_directMouse->Poll();
	if (FAILED(hr))
	{
		tools::Debug::LogError("�}�E�X�f�o�C�X�̃|�[�����O�Ɏ��s���܂����B");
		return false;
	}
	return true;
}


//==============================================================================
//!	@fn		ShutDown
//!	@brief	�I������
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::Inputsystem::ShutDown()
{
	// ���̓f�o�C�X�̐�����~����
	m_directKeyboard->Unacquire();
	m_directMouse->Unacquire();

	// IDirectInput8�̉�����s��
	m_directInput->Release();
	m_directKeyboard->Release();
	m_directMouse->Release();

	m_directMouse.Reset();
	m_directKeyboard.Reset();
	m_directInput.Reset();
	return true;
}