//*****************************************************************************
//* @file   TestEditor.h
//* @brief  
//* @note   テストエディター
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "EditorHeader.h"

namespace EDITOR_SYSTEMS
{
	class TestEditor : public systems::Editor
	{
	public:
		EDITOR_CLASS;



		// Editor を介して継承されました
		virtual void Update() override;

	};
}
