#include "ShaderManager.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "Debug.h"
#include "FileSystem.h"

USING_GAME_SYSTEMS;
USING_TOOLS;

void GAME_SYSTEMS::ShaderManager::CreateVertexShader(String filePath, D3D11_INPUT_ELEMENT_DESC* layout, uInt32 elementNum)
{
	T_String name = FileSystem::GetFileName(filePath, false);
	m_vertexShaderList[name] = std::make_shared<VertexShader>();
	m_vertexShaderList[name]->LoadShader(filePath, layout, elementNum);
}

void GAME_SYSTEMS::ShaderManager::CreatePixelShader(String filePath)
{
	T_String name = FileSystem::GetFileName(filePath, false);
	m_pixelShaderList[name] = std::make_shared<PixelShader>();
	m_pixelShaderList[name]->LoadShader(filePath);
}

SharedPtr<VertexShader> GAME_SYSTEMS::ShaderManager::GetVertexShader(T_String shaderName)
{
	if (m_vertexShaderList.contains(shaderName) == false)
	{
		tools::Debug::LogError("頂点シェーダーがありません");
		return nullptr;
	}
	return m_vertexShaderList[shaderName];
}

SharedPtr<PixelShader> GAME_SYSTEMS::ShaderManager::GetPixelShader(T_String shaderName)
{
	if (m_pixelShaderList.contains(shaderName) == false)
	{
		tools::Debug::LogError("ピクセルシェーダーがありません");
		return nullptr;
	}
	return m_pixelShaderList[shaderName];
}

void GAME_SYSTEMS::ShaderManager::SetUp()
{
	// 頂点データの定義（アニメーション対応）
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEINDEX",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	CreateVertexShader(TEXT("Shader/vsoneskin.fx"), layout, ARRAYSIZE(layout));
	CreatePixelShader(TEXT("Shader/graymanps.fx"));
}

void GAME_SYSTEMS::ShaderManager::ShutDown()
{
	m_vertexShaderList.clear();
	m_pixelShaderList.clear();
}
