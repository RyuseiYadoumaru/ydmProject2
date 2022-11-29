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
#include "ResourceManager.h"
#include "Texture.h"

#include "../System/Shader.h"
#include "../System/DirectxGraphics.h"
#include "../System/MessageWindow.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;
USING_DIRECTX;

bool Material::LoadShader(T_String vertexShaderName, T_String pixelShaderName)
{
	// 頂点シェーダーセット
	bool sts = SetVertexShader(vertexShaderName);
	if (sts == false)
	{
		return false;
	}

	// ピクセルシェーダーセット
	sts = SetPixelShader(pixelShaderName);
	if (sts == false)
	{
		return false;
	}

	// 白のテクスチャをセットする
	AddTexture(ResourceManager::GetInstance()->GetTexture(TEXT("white.bmp")), 0);
	return true;
}

bool GAME_SYSTEMS::Material::SetPixelShader(T_String pixelShaderName)
{
	m_pixelShader = ShaderManager::GetInstance()->GetPixelShader(pixelShaderName);
	if (m_pixelShader == nullptr)
	{
		MessageWindow::GetInstance()->Error(TEXT("ピクセルシェーダが生成されていません"));
		return false;
	}
	return true;
}

bool GAME_SYSTEMS::Material::SetVertexShader(T_String vertexShaderName)
{
	m_vertexShader = ShaderManager::GetInstance()->GetVertexShader(vertexShaderName);
	if (m_vertexShader == nullptr)
	{
		MessageWindow::GetInstance()->Error(TEXT("頂点シェーダが生成されていません"));
		return false;
	}
	return true;
}

void GAME_SYSTEMS::Material::AddTexture(SharedPtr<Texture> texture, uInt32 slot)
{
	m_textureList[slot] = texture;
}

void Material::Unload()
{
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_textureList.clear();
}

void Material::SetShader()
{
	m_vertexShader->BindShader();
	m_pixelShader->BindShader();
	for (auto& tex : m_textureList)
	{
		tex.second->BindTexture(tex.first);
	}
}

Material& GAME_SYSTEMS::Material::operator=(const Material& mat) noexcept
{
	m_ambientColor = mat.m_ambientColor;
	m_diffuseColor = mat.m_diffuseColor;
	m_specularColor = mat.m_specularColor;
	if (m_vertexShader == nullptr)
	{
		m_vertexShader = std::make_shared<VertexShader>();
	}
	m_vertexShader = mat.m_vertexShader;
	if (m_pixelShader == nullptr)
	{
		m_pixelShader = std::make_shared<PixelShader>();
	}
	m_pixelShader = mat.m_pixelShader;
	m_textureList = mat.m_textureList;
	return *this;
}
