//*****************************************************************************
//* @file   Material.cpp
//* @brief  ƒ}ƒeƒŠƒAƒ‹
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

USING_GAME_SYSTEMS;
USING_SYSTEMS;
USING_DIRECTX;

bool Material::LoadShader(T_String vertexShaderName, T_String pixelShaderName)
{
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
	m_vertexShader->BindShader();
	m_pixelShader->BindShader();
}