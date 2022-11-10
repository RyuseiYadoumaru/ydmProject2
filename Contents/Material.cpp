//*****************************************************************************
//* @file   Material.cpp
//* @brief  マテリアル
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Material.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ShaderManager.h"

#include "../System/Shader.h"
#include "../System/DirectxGraphics.h"
#include "../System/MessageWindow.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;
USING_DIRECTX;

bool Material::LoadShader(T_String vertexShaderName, T_String pixelShaderName)
{
	// シェーダーセット
	m_vertexShader = ShaderManager::GetInstance()->GetVertexShader(vertexShaderName);
	m_pixelShader  = ShaderManager::GetInstance()->GetPixelShader(pixelShaderName);
	
	return true;
}

void Material::Unload()
{
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
}

void Material::SetShader()
{
	// マテリアル定数バッファ生成
	ID3D11Device& device = DirectXGraphics::GetInstance()->GetDevice();
	bool sts = CreateConstantBufferWrite(&device,
		sizeof(Material::ConstantBuffer),
		m_cbMaterial.GetAddressOf());

	if (sts == false)
	{
		MessageWindow::Error("[Material::ConstantBuffer]の生成に失敗");
		return;
	}

	// 定数バッファ更新
	ID3D11DeviceContext& devicecontext = DirectXGraphics::GetInstance()->GetImmediateContext();
	D3D11_MAPPED_SUBRESOURCE pData;
	Material::ConstantBuffer cb;
	cb.ambientColor.w = 1.0f;
	cb.ambientColor.x = m_ambientColor.r;
	cb.ambientColor.y = m_ambientColor.g;
	cb.ambientColor.z = m_ambientColor.b;

	cb.diffuseColor.w = 1.0f;
	cb.diffuseColor.x = m_diffuseColor.r;
	cb.diffuseColor.y = m_diffuseColor.g;
	cb.diffuseColor.z = m_diffuseColor.b;

	cb.specularColor.w = 1.0f;
	cb.specularColor.x = m_specularColor.r;
	cb.specularColor.y = m_specularColor.g;
	cb.specularColor.z = m_specularColor.b;

	HRESULT hr = devicecontext.Map(m_cbMaterial.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr))
	{
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(Material::ConstantBuffer));
		devicecontext.Unmap(m_cbMaterial.Get(), 0);
	}

	m_vertexShader->BindShader();
	m_pixelShader->BindShader();
	SetConstantBuffer();
}

void GAME_SYSTEMS::Material::SetConstantBuffer()
{
	ID3D11DeviceContext& devcon = DirectXGraphics::GetInstance()->GetImmediateContext();
	// マテリアルをVSへセット
	devcon.VSSetConstantBuffers(3, 1, &m_cbMaterial);
	devcon.PSSetConstantBuffers(3, 1, &m_cbMaterial);
}
