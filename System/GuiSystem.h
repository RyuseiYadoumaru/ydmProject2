//*****************************************************************************
//* @file   GuiSystem.h
//* @brief  GUI�̃V�X�e��
//* @note   GUI�̐ݒ������s��
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************
#pragma once
#include "Core/SubSystem.h"
#include "macro.h"
#include "std.h"

namespace systems
{
	class GuiSystem : public SubSystem
	{
		SINGLETON_CLASS(GuiSystem);
	public:
		bool SetUp()	override;
		bool ShutDown() override;
		bool Run();

		void EditorSetUp();
	};
}

