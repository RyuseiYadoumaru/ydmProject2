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
		void BindShader();

	public:
		PixelShader& operator=(const PixelShader pixel) noexcept
		{
			m_pixelShader = pixel.m_pixelShader;
			return *this;
		}

	private:
		ComPtr<ID3D11PixelShader> m_pixelShader = nullptr;
	};
}
