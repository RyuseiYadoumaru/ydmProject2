//*****************************************************************************
//* @file   PixelShader.h
//* @brief  ピクセルシェーダー
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"


namespace GAME_SYSTEMS
{
	class PixelShader
	{
	public:
		bool LoadShader(T_String psFilePath);
		void Releace();
		void SetShader();

	private:
		ComPtr<ID3D11PixelShader> m_pixelShader = nullptr;

	};
}
