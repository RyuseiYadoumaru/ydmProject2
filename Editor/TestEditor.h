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
		virtual void Update() override;

	private:
		bool m_isDevelop = false;

	};
}
