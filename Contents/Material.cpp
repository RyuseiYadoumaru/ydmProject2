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
	if (m_vertexShader == nullptr)
	{
		MessageWindow::GetInstance()->Error(TEXT("頂点シェーダが生成されていません"));
		return false;
	}
	m_pixelShader  = ShaderManager::GetInstance()->GetPixelShader(pixelShaderName);
	if (m_pixelShader == nullptr)
	{
		MessageWindow::GetInstance()->Error(TEXT("ピクセルシェーダが生成されていません"));
		return false;
	}
	return true;
}

void Material::Unload()
{
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
}

void Material::SetShader()
{
	m_vertexShader->BindShader();
	m_pixelShader->BindShader();
}