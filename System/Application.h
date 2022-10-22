//*****************************************************************************
//* @file   Application.h
//* @brief  アプリケーションクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "std.h"
#include "macro.h"

class Application final
{
	COPY_PROHIBITED(Application)

public:
	static Application& Instance() noexcept
	{
		static Application application;
		return application;
	}

public:
	bool SetUp(HINSTANCE h_instance, int windowMode);
	uInt16 Run();
	bool ShutDown();


public:
	const bool	SetUpComplete()	const noexcept { return m_isSetUpComplete; }
	HINSTANCE	GetHInstance()	const noexcept { return m_hInstance; }
	const int	GetWindowMode() const noexcept { return m_windowMode; }

private:
	bool SystemCreate();
	void SystemReleace();

private:
	HINSTANCE	m_hInstance = nullptr;
	int			m_windowMode = NULL;

	bool m_isSetUpComplete = false;

private:
	Application() = default;
	~Application() = default;


};