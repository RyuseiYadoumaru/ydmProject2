//*****************************************************************************
//* @file   AudioSystem.h
//* @brief  サウンドシステム
//* @note   XAudio2を使用
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include <xaudio2.h>
#include <wrl/client.h>
#include "std.h"
#include "macro.h"
#include "Core/SubSystem.h"
using Microsoft::WRL::ComPtr;

namespace systems
{
	class AudioSystem final : public SubSystem
	{
		SINGLETON_CLASS(AudioSystem);
	public:
		bool SetUp()	override;
		bool ShutDown() override;

	public:
		IXAudio2* GetIXAudio2() noexcept { return m_xAudio2.Get(); }
		IXAudio2MasteringVoice* GetXAudio2MasteringVoice() noexcept { return m_masteringVoice; }

	private:

		/**
		 * XAudio2インターフェース
		 * 全てのオーディオエンジンの状態、処理スレッド、音声グラフを管理する.
		 */
		ComPtr<IXAudio2> m_xAudio2 = nullptr;

		/**
		 * マスタリングボイス
		 * オーディオ出力デバイスを表すときに使用する
		 * ComPtrだと謎にエラーが発生してしまうため普通のポインタ変数で扱ってます.
		 */
		IXAudio2MasteringVoice* m_masteringVoice = nullptr;

	};
}
