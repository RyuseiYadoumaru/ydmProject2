//*****************************************************************************
//* @file   DX11SetMaterial.cpp
//* @brief  
//* @note   マテリアルに必要なデータを定数バッファにセットする
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "DX11SetMaterial.h"
#include "MessageWindow.h"
#include "Material.h"

bool SYSTEMS::DX11SetMaterial::Initialize()
{
	ID3D11Device& device = systems::DirectXGraphics::GetInstance()->GetDevice();

	bool sts = CreateConstantBuffer(
		&device,
		sizeof(ConstantBufferMaterial),
		m_constantBufferMaterial.GetAddressOf());
	if (sts == false)
	{
		MessageWindow::Error(TEXT("ConstantBufferMaterialの生成に失敗！"));
		return false;
	}
	return true;
}

bool SYSTEMS::DX11SetMaterial::Finalize()
{
	if (m_constantBufferMaterial != nullptr)
	{
		m_constantBufferMaterial = nullptr;
	}
	return true;
}

void SYSTEMS::DX11SetMaterial::SetConstantBuffer(const GAME_SYSTEMS::Material& material)
{
	m_cbMaterial.AmbientColor.w = 1.0f;
	m_cbMaterial.AmbientColor.x = material.GetAmbientColor().r;
	m_cbMaterial.AmbientColor.y = material.GetAmbientColor().g;
	m_cbMaterial.AmbientColor.z = material.GetAmbientColor().b;

	m_cbMaterial.DiffuseColor.w = 1.0f;
	m_cbMaterial.DiffuseColor.x = material.GetDiffuseColor().r;
	m_cbMaterial.DiffuseColor.y = material.GetDiffuseColor().g;
	m_cbMaterial.DiffuseColor.z = material.GetDiffuseColor().b;

	m_cbMaterial.SpecularColor.w = 1.0f;
	m_cbMaterial.SpecularColor.x = material.GetSpecularColor().r;
	m_cbMaterial.SpecularColor.y = material.GetSpecularColor().g;
	m_cbMaterial.SpecularColor.z = material.GetSpecularColor().b;

	ID3D11DeviceContext& devicecontext = systems::DirectXGraphics::GetInstance()->GetImmediateContext();
	devicecontext.UpdateSubresource(
		m_constantBufferMaterial.Get(),
		0,
		nullptr,
		&m_cbMaterial,
		0,
		0);

	devicecontext.VSSetConstantBuffers(3, 1, m_constantBufferMaterial.GetAddressOf());
	devicecontext.PSSetConstantBuffers(3, 1, m_constantBufferMaterial.GetAddressOf());
	
}
