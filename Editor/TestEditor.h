//*****************************************************************************
//* @file   TestEditor.h
//* @brief  
//* @note   �e�X�g�G�f�B�^�[
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
		EDITOR_CLASS;

	private:
		virtual void Update() override;

	private:
		bool m_isDevelop = false;

	};
}
