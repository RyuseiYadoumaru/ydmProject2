//*****************************************************************************
//* @file   Line.h
//* @brief  
//* @note   ƒ‰ƒCƒ“
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "std.h"
#include "macro.h"


namespace GAME_SYSTEMS
{
	class VertexShader;
	class PixelShader;
	class Line
	{
	public:
		struct Vertex
		{
			DirectX::XMFLOAT3 Position;
			DirectX::XMFLOAT4 Color;
		};

	public:
		void Load(Vector<Vertex> vertex);
		void Releace();
		void Render();

		void SetVertex(Vector<Vertex> vertex);
	private:
		uInt32 m_vertexSize = 2;

		SharedPtr<VertexShader> m_vertexShader = nullptr;
		SharedPtr<PixelShader> m_pixelShader = nullptr;
		ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;

	};
}
