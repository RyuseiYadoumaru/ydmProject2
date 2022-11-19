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

	private:
		ComPtr<ID3D11ShaderResourceView> m_srv = nullptr;

	};
}
