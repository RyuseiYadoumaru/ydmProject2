//*****************************************************************************
//* @file   AudioSystem.cpp
//* @brief  サウンドシステム
//* @note   音関係のシステム
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
//!	@brief	初期化
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::AudioSystem::SetUp()
{
	HRESULT hr;
	HANDLE hFile;

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	DWORD fileType;

	//COM初期化
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		tools::Debug::LogError("AudioCOM初期化に失敗しました");
		return false;
	}

	//XAudio2生成
	hr = XAudio2Create(&m_xAudio2, XAUDIO_FLAG);
	if (FAILED(hr))
	{
		tools::Debug::LogError("XAudio2の生成に失敗しました");
		CoUninitialize();
		return false;
	}

	//マスターリングボイス生成
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if (FAILED(hr))
	{
		tools::Debug::LogError("MasteringVoiceの生成に失敗しました");
		if (m_xAudio2 != nullptr) m_xAudio2->Release();
		CoUninitialize();
		return false;

	}

	return true;
}


//==============================================================================
//!	@fn		ShutDown
//!	@brief	終了処理
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::AudioSystem::ShutDown()
{
	m_masteringVoice->DestroyVoice();

	if (m_xAudio2 != nullptr) m_xAudio2->Release();

	// ＣＯＭの破棄
	CoUninitialize();

	/** 解放 */
	m_xAudio2.Reset();
	SAFE_DELETE(m_masteringVoice);

	return true;
}