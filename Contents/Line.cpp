//*****************************************************************************
//* @file   Line.cpp
//* @brief  
//* @note   ライン
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#include "Line.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ShaderManager.h"

#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"
#include "../System/MessageWindow.h"

void GAME_SYSTEMS::Line::Load(Vector<Vertex> vertex)
{
	m_vertexShader = ShaderManager::GetInstance()->GetVertexShader("DebugVertexShader");
	m_pixelShader = ShaderManager::GetInstance()->GetPixelShader("DebugPixelShader");
	
	ID3D11Device* device = &SYSTEMS::DirectXGraphics::GetInstance()->GetDevice();

	bool sts = CreateVertexBufferWrite(device, sizeof(Line::Vertex), static_cast<uInt32>(vertex.size()), (void*)vertex.data(), m_vertexBuffer.GetAddressOf());
	if (!sts) 
	{
		SYSTEMS::MessageWindow::GetInstance()->Error(TEXT("CreateVertexBufferWrite(Line) error"));
		return;
	}
	m_vertexSize = static_cast<uInt32>(vertex.size());
}

void GAME_SYSTEMS::Line::Releace()
{
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
}

void GAME_SYSTEMS::Line::Render()
{
	ID3D11DeviceContext& deviceContext = SYSTEMS::DirectXGraphics::GetInstance()->GetImmediateContext();
	// 頂点バッファをセットする
	unsigned int stride = sizeof(Line::Vertex);
	unsigned  offset = 0;
	deviceContext.IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	m_vertexShader->BindShader();
	m_pixelShader->BindShader();
	deviceContext.Draw(m_vertexSize, 0);

}

void GAME_SYSTEMS::Line::SetVertex(Vector<Vertex> vertex)
{
	D3D11_MAPPED_SUBRESOURCE pData;

	ID3D11DeviceContext& deviceContext = SYSTEMS::DirectXGraphics::GetInstance()->GetImmediateContext();
	HRESULT hr = deviceContext.Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) 
	{
		memcpy_s(pData.pData, pData.RowPitch, (void*)(vertex.data()), sizeof(Vertex) * vertex.size());
		deviceContext.Unmap(m_vertexBuffer.Get(), 0);
	}
	m_vertexSize = static_cast<uInt32>(vertex.size());
}
