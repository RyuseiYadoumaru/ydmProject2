#include "Polygon.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;
USING_DIRECTX;

Polygon::Polygon(Vector<Vertex> vertices, Vector<uInt32> indices)
{
	this->m_vertices = vertices;
	this->m_indices = indices;
	InitBuffers();
}

Polygon::Polygon(Vector<Vertex_Cube> vertices, Vector<uInt32> indices)
{
}

void Polygon::Uninit()
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

void Polygon::Draw(ID3D11DeviceContext* devcon)
{
	uInt32 stride = sizeof(Vertex);
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

bool Polygon::InitBuffers()
{
	ID3D11Device& dev = DirectXGraphics::GetInstance()->GetDevice();

	// 頂点バッファ生成
	bool sts = CreateVertexBufferWrite(
		&dev,
		static_cast<uInt32>(sizeof(Vertex)),			// ストライド
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
