//*****************************************************************************
//* @file   Polygon.h
//* @brief  ポリゴン
//* @note   テンプレートで頂点バッファのレイアウトを定義します
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"
#include <DirectXMath.h>
#include <d3d11.h>

namespace GAME_SYSTEMS
{
	template<class VERTEX_TYPE>
	class Polygon
	{
	public:
		Polygon(Vector<VERTEX_TYPE> vertices, Vector<uInt32> indices)
		{
			m_vertices = vertices;
			m_indices = indices;
			InitBuffers();
		}
		~Polygon() = default;
	public:
		void Uninit()
		{
			if (this->m_vertexBuffer == nullptr)
			{
				this->m_vertexBuffer->Release();
				this->m_vertexBuffer = nullptr;
			}

			if (this->m_indexBuffer == nullptr)
			{
				this->m_indexBuffer->Release();
				this->m_indexBuffer = nullptr;
			}
		}

		void Draw(ID3D11DeviceContext* devcon)
		{
			uInt32 stride = sizeof(VERTEX_TYPE);
			uInt32 offset = 0;
			// 頂点バッファをセット
			devcon->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
			// インデックスバッファをセット
			devcon->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			// トポロジーをセット
			devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			// インデックスバッファを利用して描画
			devcon->DrawIndexed(static_cast<uInt32>(m_indices.size()), 0, 0);
		}


	private:
		bool InitBuffers()
		{
			ID3D11Device& dev = SYSTEMS::DirectXGraphics::GetInstance()->GetDevice();

			// 頂点バッファ生成
			bool sts = CreateVertexBufferWrite(
				&dev,
				static_cast<uInt32>(sizeof(VERTEX_TYPE)),			// ストライド
				static_cast<uInt32>(this->m_vertices.size()),		// 頂点数
				m_vertices.data(),									// 頂点データ
				m_vertexBuffer.GetAddressOf());
			if (sts == false)
			{
				return false;
			}

			// インデックスバッファ生成
			sts = CreateIndexBuffer(
				&dev,
				static_cast<uInt32>(m_indices.size()),
				m_indices.data(),
				m_indexBuffer.GetAddressOf());
			if (sts == false)
			{
				return false;
			}
			return true;
		}
	
	private:
		Vector<VERTEX_TYPE> m_vertices;		// 頂点データ		
		Vector<uInt32> m_indices;			//  インデックスデータ
	
		ComPtr<ID3D11Buffer> m_vertexBuffer;
		ComPtr<ID3D11Buffer> m_indexBuffer;
	};
}