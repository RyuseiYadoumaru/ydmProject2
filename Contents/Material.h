//*****************************************************************************
//* @file   Material.h
//* @brief  �}�e���A��
//* @note   
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
	class VertexShader;
	class PixelShader;

	class Material
	{
	public:
		Material() = default;
		~Material() = default;

	public:
		bool LoadShader();
		void Unload();
		void SetShader();

	private:
		SharedPtr<VertexShader> m_vertexShader	= nullptr;
		SharedPtr<PixelShader> m_pixelShader	= nullptr;
	};
}


