//*****************************************************************************
//* @file   Editor.h
//* @brief  
//* @note   エディターの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include <DirectXMath.h>

#define EDITOR_CLASS using systems::Editor::Editor;

namespace SYSTEMS
{
	class Editor
	{
	public:
		void Initialize();
		void Render();


	public:
		explicit Editor(T_String name, Float32 posX, Float32 posY) :
			m_windowName(name),
			m_position(posX, posY){ }
		~Editor() = default;
	
	private:
		virtual void Update() = 0;

	private:
		T_String m_windowName;
		DirectX::XMFLOAT2 m_position;

	};
}

