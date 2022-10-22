//*****************************************************************************
//* @file   Framelate.h
//* @brief  
//* @note   フレームの管理を行う。
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "GameSubSysmte.h"

namespace gameSystems
{
	class Framelate : public GameSubSystem
	{
		GAMESUBSYSTEM;
	public:
		bool Initialize() override;
		bool Run() override;
		bool Finalize() override;

	public:
		const Float32 GetDeltaTime() const noexcept { return m_deltaTime; }
		const uInt64 GetTotalFrame() const noexcept { return m_totalFrameCount; }
		const Float64 GetTotalTime() const noexcept { return m_totalTime; }
		const Float64 GetGameTotalTime() const noexcept { return m_gameTotalTime; }
		const bool GetFixed() const noexcept { return m_isfixed; }

		const Float32 GetTimeScale() const noexcept { return m_scale; }
		void SetTimeScale(Float32 scale) noexcept { m_scale = scale; }

	private:
		void CheckFixedFrame();
		void Wait();
		void PrintFPS();

	private:
		Float32 m_deltaTime = 0.0f;
		Float32 m_currentTime = 0.0f;
		Float32 m_lastTime = 0.0f;
		uInt64  m_totalFrameCount = 0;
		Float64 m_totalTime = 0.0f;
		Float64 m_gameTotalTime = 0.0f;

		Float32 m_saveTime = 0.0f;
		Float32 m_nowFPS = 60;

		Float32 m_scale = 1.0f;
		bool	m_isfixed;
	};
}
