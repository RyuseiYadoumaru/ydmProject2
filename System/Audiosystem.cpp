//*****************************************************************************
//* @file   AudioSystem.cpp
//* @brief  �T�E���h�V�X�e��
//* @note   ���֌W�̃V�X�e��
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************

#include "AudioSystem.h"
#include "Debug.h"
#include "std.h"

#ifdef  _DEBUG
#define XAUDIO_FLAG (XAUDIO2_DEBUG_ENGINE)
#else
#define XAUDIO_FLAG (0)
#endif //  _DEBUG


//==============================================================================
//!	@fn		SetUp
//!	@brief	������
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::AudioSystem::SetUp()
{
	HRESULT hr;
	HANDLE hFile;

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	DWORD fileType;

	//COM������
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		tools::Debug::LogError("AudioCOM�������Ɏ��s���܂���");
		return false;
	}

	//XAudio2����
	hr = XAudio2Create(&m_xAudio2, XAUDIO_FLAG);
	if (FAILED(hr))
	{
		tools::Debug::LogError("XAudio2�̐����Ɏ��s���܂���");
		CoUninitialize();
		return false;
	}

	//�}�X�^�[�����O�{�C�X����
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if (FAILED(hr))
	{
		tools::Debug::LogError("MasteringVoice�̐����Ɏ��s���܂���");
		if (m_xAudio2 != nullptr) m_xAudio2->Release();
		CoUninitialize();
		return false;

	}

	return true;
}


//==============================================================================
//!	@fn		ShutDown
//!	@brief	�I������
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::AudioSystem::ShutDown()
{
	m_masteringVoice->DestroyVoice();

	if (m_xAudio2 != nullptr) m_xAudio2->Release();

	// �b�n�l�̔j��
	CoUninitialize();

	/** ��� */
	m_xAudio2.Reset();
	SAFE_DELETE(m_masteringVoice);

	return true;
}