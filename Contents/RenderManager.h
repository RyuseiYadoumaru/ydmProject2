//*****************************************************************************
//* @file   RenderManager.h
//* @brief  
//* @note   描画のコンポーネントの管理とウィンドウの描画を担当する
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