//*****************************************************************************
//* @file   Framelate.h
//* @brief  
//* @note   フレームの管理を行う。
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include <chrono>
#include <thread>
#include "Framelate.h"
#include "SystemTimer.h"
#include "Window.h"
#include "Debug.h"

USING_SYSTEMS;

/**============================================================================
//! @func   Initialize
//! @brief  初期化
//! @retval true:正常終了　false:異常終了
============================================================================*/
bool gameSystems::Framelate::Initialize()
{
    m_deltaTime = 0.0f;
	m_currentTime = 0.0f;
	m_lastTime = 0.0f;
	m_totalFrameCount = 0;
	m_totalTime = 0.0f;
	m_gameTotalTime = 0.0f;
	m_scale = 1.0f;
	m_nowFPS = 0.0f;
	m_saveTime = 0.0f;

	return true;

}

/**============================================================================
//! @func   Run
//! @brief  更新
//! @retval true:正常終了　false:異常終了
============================================================================*/
bool gameSystems::Framelate::Run()
{
	auto systemTimer = systems::SystemTimer::GetInstance();
	//現在時間取得
	Float32 nowTime = static_cast<Float32>(systemTimer->GetTime());
	m_currentTime = nowTime * 0.001f;

	//デルタタイム生成
	m_deltaTime = m_currentTime - m_lastTime;

	//前フレームの時間保存
	m_lastTime = m_currentTime;

	//フレームカウント
	m_totalFrameCount++;

	//トータルタイム
	m_totalTime += m_deltaTime;
	m_gameTotalTime += m_deltaTime * m_scale;

	/** 固定フレームチェック */
	CheckFixedFrame();

	/** 待機処理 */
	Wait();

	/** FPS出力 */
	PrintFPS();

	return true;
}


/**============================================================================
//! @func   Finalize
//! @brief  終了処理
//! @retval true:正常終了　false:異常終了
============================================================================*/
bool gameSystems::Framelate::Finalize()
{
    return true;
}


/**============================================================================
//! @func   CheckFixedFrame
//! @brief  固定フレームを更新するかチェックする
============================================================================*/
void gameSystems::Framelate::CheckFixedFrame()
{
	static Float32 fixedTime = 0.0f;
	fixedTime += m_deltaTime;
	m_isfixed = false;
	if (fixedTime >= SystemTimer::m_FPS)
	{
		m_isfixed = true;
		fixedTime = 0.0f;
	}
}


/**============================================================================
//! @func   Wait
//! @brief  待機処理
============================================================================*/
void gameSystems::Framelate::Wait()
{
	Float32 frameParam = (1.0f / static_cast<Float32>(SystemTimer::m_FPS)) * 1000000.0f;
	Float32 sleep_time = frameParam - m_deltaTime;

	if (sleep_time > 0)
	{
		float tt = sleep_time / 1000.0f;

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
	}

}

/**============================================================================
//! @func   PrintFPS
//! @brief  FPSを出力する
============================================================================*/
void gameSystems::Framelate::PrintFPS()
{
	uInt32 IntervalFrame = 60;

	/*	FPS計測	*/
	if (m_totalFrameCount % IntervalFrame == 0)
	{
		m_nowFPS = IntervalFrame / (m_currentTime - m_saveTime);
		m_saveTime = m_currentTime;

		/****	FPS表示設定	****/
		std::stringstream ss;
		ss << "FPS：" << m_nowFPS;
		std::string text = ss.str();
		systems::Window::GetInstance()->ChangeWindowText(text);
		
	}
}





