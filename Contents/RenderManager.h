//*****************************************************************************
//* @file   RenderManager.h
//* @brief  
//* @note   �`��̃R���|�[�l���g�̊Ǘ��ƃE�B���h�E�̕`���S������
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "Color.h"

namespace GAME_SYSTEMS
{
	class RenderManager
	{
		SINGLETON_CLASS(RenderManager);
		
	public:
		void ClearRenderer(myMath::Color& displayColor);
		void SwapRenderBuffer();
	};
}