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
#include "SubSystem.h"

class Application final
{
	SINGLETON_CLASS(Application);
	using SubSystemPtr = systems::SubSystem*;

public:
	bool SetUp(HINSTANCE h_instance, int windowMode);
	bool ShutDown();
	uInt16 Run();

public:
	bool RegisterSubSystem(SubSystemPtr subSystem, String subsystemName = "SubSystem");

	const bool	SetUpComplete()	const noexcept { return m_isSetUpComplete; }
	HINSTANCE	GetHInstance()	const noexcept { return m_hInstance; }
	const int	GetWindowMode() const noexcept { return m_windowMode; }

private:
	void SystemReleace();

private:
	Vector<SubSystemPtr> m_subSystems;
	HINSTANCE	m_hInstance = nullptr;
	int			m_windowMode = NULL;
	bool m_isSetUpComplete = false;
};