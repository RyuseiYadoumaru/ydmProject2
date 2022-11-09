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

#include "../System/Shader.h"
#include "../System/DirectxGraphics.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;
USING_DIRECTX;

bool Material::LoadShader()
{
	m_vertexShader = std::make_shared<VertexShader>();
	m_pixelShader = std::make_shared<PixelShader>();

	m_vertexShader->LoadShader(TEXT("Shader/vsoneskin.fx"));
	m_pixelShader->LoadShader(TEXT("Shader/graymanps.fx"));
	return true;
}

void Material::Unload()
{
	if (m_vertexShader != nullptr)
	{
		m_vertexShader->Releace();
		m_vertexShader = nullptr;
	}
	if (m_pixelShader != nullptr)
	{
		m_pixelShader->Releace();
		m_pixelShader = nullptr;
	}

}

void Material::SetShader()
{
	m_vertexShader->SetShader();
	m_pixelShader->SetShader();
}