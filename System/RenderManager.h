//*****************************************************************************
//* @file   RenderManager.h
//* @brief  
//* @note   描画のコンポーネントの管理とウィンドウの描画を担当する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "Color.h"

namespace SYSTEMS
{
	class RenderManager
	{
		SINGLETON_CLASS(RenderManager);
		
	public:
		void SetScreenColor(float r, float g, float b) noexcept { m_screenColor = { r, g, b }; }
		void ClearRenderer();
		void SwapRenderBuffer();

	private:
		DirectX::XMFLOAT3 m_screenColor = { 1.0f, 1.0f, 1.0f };



	};
}