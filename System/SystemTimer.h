//******************************************************************************
//* @file   SystemTimer.h
//* @brief  �V�X�e���^�C�}�[�N���X
//* @note   �V�X�e����̎��Ԃ��Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "std.h"
#include "macro.h"
#include "SubSystem.h"

namespace systems
{
	class SystemTimer final : public SubSystem
	{
		SINGLETON_CLASS(SystemTimer);
	public:
		bool SetUp()	override;
		bool ShutDown() override;

		uInt64 GetTime() noexcept { return timeGetTime(); }
	};
}