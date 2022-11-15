//*****************************************************************************
//* @file   Material.cpp
//* @brief  �}�e���A��
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
	// �V�F�[�_�[�Z�b�g
	m_vertexShader = ShaderManager::GetInstance()->GetVertexShader(vertexShaderName);
	if (m_vertexShader == nullptr)
	{
		MessageWindow::GetInstance()->Error(TEXT("���_�V�F�[�_����������Ă��܂���"));
		return false;
	}
	m_pixelShader  = ShaderManager::GetInstance()->GetPixelShader(pixelShaderName);
	if (m_pixelShader == nullptr)
	{
		MessageWindow::GetInstance()->Error(TEXT("�s�N�Z���V�F�[�_����������Ă��܂���"));
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