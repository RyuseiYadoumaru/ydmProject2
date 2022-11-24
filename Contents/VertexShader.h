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
		bool LoadShader(T_String vsFilePath, D3D11_INPUT_ELEMENT_DESC* layout, uInt32 elementsNum);
		void Releace();
		void BindShader();

	public:
		//VertexShader& operator=(const VertexShader& vertex) noexcept
		//{
		//	m_vertexShader = vertex.m_vertexShader;
		//	m_vertexLayout = vertex.m_vertexLayout;
		//	return *this;
		//}

	private:
		ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
		ComPtr<ID3D11InputLayout> m_vertexLayout = nullptr;
		
	};
}
