//*****************************************************************************
//* @file   Console.h
//* @brief  コンソールクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "../SystemBase.h"
#include "std.h"

namespace systems
{
	class Console final : public SystemBase<Console>
	{
	public:
		bool SetUp() override;
		bool ShutDown() override;

		void TextColor(WORD color);

	public:
		const HANDLE& GetHandle() const { return m_stdOutHandle; }

	private:
		HANDLE		m_stdOutHandle;
		WORD		m_wAttributes;
		FILE*		m_fp;

	};

}
