//*****************************************************************************
//* @file   VertexShader.h
//* @brief  頂点シェーダー
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
	class VertexShader
	{
	public:
		bool LoadShader(T_String vsFilePath);
		void Releace();
		void SetShader();

	private:
		ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
		ComPtr<ID3D11InputLayout> m_vertexLayout = nullptr;
		
	};
}
