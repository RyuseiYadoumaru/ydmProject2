//*****************************************************************************
//* @file   VertexShader.h
//* @brief  ���_�V�F�[�_�[
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

	private:
		ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
		ComPtr<ID3D11InputLayout> m_vertexLayout = nullptr;
		
	};
}