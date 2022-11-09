//*****************************************************************************
//* @file   RenderManager.h
//* @brief  
//* @note   �`��̃R���|�[�l���g�̊Ǘ��ƃE�B���h�E�̕`���S������
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "ManagerHeader.h"
#include "Color.h"

namespace GAME_SYSTEMS
{
	class RenderManager
	{
		SINGLETON_CLASS(RenderManager);
		MANAGER_CLASS;
		
	public:
		void ClearRenderer(myMath::Color& displayColor);
		void SwapRenderBuffer();
	};
}