//*****************************************************************************
//* @file   Console.h
//* @brief  コンソールクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "Core/SubSystem.h"
#include "std.h"
#include "macro.h"
namespace systems
{
	class Console final : public SubSystem
	{
		SINGLETON_CLASS(Console);
	public:
		bool SetUp()	override;
		bool ShutDown() override;

		void TextColor(WORD color);

	public:
		const HANDLE& GetHandle() const noexcept { return m_stdOutHandle; }

	private:
		HANDLE		m_stdOutHandle = NULL;
		WORD		m_wAttributes = NULL;
		FILE*		m_fp = nullptr;

	};
}
