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
	if (m_vertexShaderList.contains(name) == true)
	{
		TOOLS::Debug::Log("既に生成されています：", name);
		return;
	}

	m_vertexShaderList[name] = std::make_shared<VertexShader>();
	m_vertexShaderList[name]->LoadShader(filePath, layout, elementNum);
}

void GAME_SYSTEMS::ShaderManager::CreatePixelShader(String filePath)
{
	T_String name = FileSystem::GetFileName(filePath, false);
	if (m_pixelShaderList.contains(name) == true)
	{
		TOOLS::Debug::Log("既に生成されています：", name);
		return;
	}
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
	D3D11_INPUT_ELEMENT_DESC layoutShape[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	CreateVertexShader(TEXT("Shader/DefaultMeshVertexShader.hlsl"), layoutShape, ARRAYSIZE(layoutShape));

	// 頂点データの定義（アニメーション対応）
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEINDEX",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	CreateVertexShader(TEXT("Shader/SkinnedVertexShader.hlsl"), layout, ARRAYSIZE(layout));
	
	// デバッグ用シェーダー
	D3D11_INPUT_ELEMENT_DESC layoutDebug[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	CreateVertexShader(TEXT("Shader/DebugVertexShader.hlsl"), layoutDebug, ARRAYSIZE(layoutDebug));
	CreateVertexShader(TEXT("Shader/DebugColliderVertexShader.hlsl"), layoutDebug, ARRAYSIZE(layoutDebug));
	CreatePixelShader(TEXT("Shader/DebugPixelShader.hlsl"));


	CreatePixelShader(TEXT("Shader/ShapePixelShader.hlsl"));
	CreatePixelShader(TEXT("Shader/GrayManps.hlsl"));
	CreatePixelShader(TEXT("Shader/UnlitDefaultPixelShader.hlsl"));
	CreatePixelShader(TEXT("Shader/DefaultMeshPixelShader.hlsl"));
}

void GAME_SYSTEMS::ShaderManager::ShutDown()
{
	m_vertexShaderList.clear();
	m_pixelShaderList.clear();
}
