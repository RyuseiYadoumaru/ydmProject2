//*****************************************************************************
//* @file   Inputsystem.h
//* @brief  インプットシステム
//* @note   入力系のセットアップを行う
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include <dinput.h>
#include "std.h"
#include "macro.h"
#include "SubSystem.h"

#pragma comment (lib,"dinput8.lib")
#pragma comment (lib, "dxguid.lib")

namespace systems
{
	class Inputsystem final : public SubSystem
	{
		SINGLETON_CLASS(Inputsystem);
	public:
		bool SetUp()	override;
		bool ShutDown() override;

		IDirectInput8*		 GetDirectInput()	 noexcept { return m_directInput.Get();}
		IDirectInputDevice8* GetDirectKeyboard() noexcept { return m_directKeyboard.Get(); }
		IDirectInputDevice8* GetDirectMouse()	 noexcept { return m_directMouse.Get(); }

	private:
		ComPtr<IDirectInput8>		m_directInput	 =	nullptr;
		ComPtr<IDirectInputDevice8>	m_directKeyboard =	nullptr;
		ComPtr<IDirectInputDevice8> m_directMouse	 =	nullptr;
	};
}