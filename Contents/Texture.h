//*****************************************************************************
//* @file   Texture.h
//* @brief  
//* @note   テクスチャ
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <d3d11.h>
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class Texture
	{
	public:
		void Load(T_String fileName);
		void BindTexture(uInt32 registerIndex);
		void Releace();

	public:
		Texture& operator=(const Texture& texture) noexcept { m_srv = texture.m_srv; return *this; }

	private:
		ComPtr<ID3D11ShaderResourceView> m_srv = nullptr;

	};
}
