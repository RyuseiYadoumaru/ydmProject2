//*****************************************************************************
//* @file   Material.h
//* @brief  ƒ}ƒeƒŠƒAƒ‹
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
		bool LoadShader(T_String vertexShaderName, T_String pixelShaderName);
		void Unload();
		void SetShader();

	private:
		SharedPtr<VertexShader> m_vertexShader	= nullptr;
		SharedPtr<PixelShader> m_pixelShader	= nullptr;
	};
}


