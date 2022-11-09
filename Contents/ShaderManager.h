//*****************************************************************************
//* @file   ShaderManager.h
//* @brief  
//* @note   シェーダー管理
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "ManagerHeader.h"

namespace GAME_SYSTEMS
{
	class VertexShader;
	class PixelShader;

	class ShaderManager
	{
		SINGLETON_CLASS(ShaderManager);
		MANAGER_CLASS;

	public:
		void CreateVertexShader(String filePath, D3D11_INPUT_ELEMENT_DESC* layout, uInt32 elementNum);
		void CreatePixelShader(String filePath);
		SharedPtr<VertexShader> GetVertexShader(T_String shaderName);
		SharedPtr<PixelShader> GetPixelShader(T_String shaderName);

	private:
		void SetUp();
		void ShutDown();

	private:
		Unordered_Map<T_String, SharedPtr<VertexShader>> m_vertexShaderList;
		Unordered_Map<T_String, SharedPtr<PixelShader>>  m_pixelShaderList;

	};
}
