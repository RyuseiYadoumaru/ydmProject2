//******************************************************************************
//* @file   Shader.h
//* @brief  
//* @note   シェーダー周りの読み込みを行う
//* 
//* @author YadoumaruRyusei
//* @date   December 2021
//*****************************************************************************

#pragma once
#include	<d3dcompiler.h>
#include	<directxmath.h>
#include	<DirectXMath.h>
#include	<locale.h>
#include	<d3d11.h>

#include	"ThirdParty/DirectTex/WICTextureLoader.h"
#include	"ThirdParty/DirectTex/DDSTextureLoader.h"
#include	"ThirdParty/DirectTex/DirectXTex.h"

#include "std.h"
#include "macro.h"

USING_DIRECTX;

HRESULT CompileShaderFromFile(
	const T_Char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3DBlob** ppBlobOut);

bool CreateConstantBuffer(
	ID3D11Device* device,
	unsigned int bytesize,
	ID3D11Buffer** pConstantBuffer			// コンスタントバッファ
);

bool CreateConstantBufferWrite(
	ID3D11Device* device,
	unsigned int bytesize,
	ID3D11Buffer** pConstantBuffer			// コンスタントバッファ
);


bool CreateIndexBuffer(
	ID3D11Device* device,
	unsigned int indexnum,	// 頂点数
	void* indexdata,							// インデックスデータ格納メモリ先頭アドレス
	ID3D11Buffer** pIndexBuffer);

bool CreateVertexBuffer(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,										// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer							// 頂点バッファ
);

bool CreateVertexBufferWrite(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);

bool CreateVertexBufferUAV(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);

bool CreateStructuredBuffer(
	ID3D11Device* device,
	unsigned int stride,				// ストライドバイト数
	unsigned int num,					// 個数
	void* data,							// データ格納メモリ先頭アドレス
	ID3D11Buffer** pStructuredBuffer	// StructuredBuffer
);

ID3D11Buffer* CreateAndCopyToBuffer(
	ID3D11Device* device,
	ID3D11DeviceContext* devicecontext,
	ID3D11Buffer* pBuffer	// RWStructuredBuffer
);

bool CreateShaderResourceView(			// バッファからシェーダーリソースビューを作成する	
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,	// Buffer
	ID3D11ShaderResourceView** ppSRV);

bool CreateUnOrderAccessView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,	// Buffer
	ID3D11UnorderedAccessView** ppUAV);

bool CreatetSRVfromTGAFile(const T_Char* filename,					// TGAファイルからシェーダーリソースビューを作成する
	ID3D11Device* device,
	ID3D11ShaderResourceView** srv);

bool CreatetSRVfromWICFile(const T_Char* filename,					// WICファイルからシェーダーリソースビューを作成する
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11ShaderResourceView** srv);

bool CreateVertexShader(ID3D11Device* device,						// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	const T_Char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout,
	unsigned int numElements,
	ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout);


bool CreatePixelShader(ID3D11Device* device,						// ピクセルシェーダーオブジェクトを生成
	const T_Char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3D11PixelShader** ppPixelShader);

bool CreatetSRVfromDDS(const T_Char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11ShaderResourceView** srv);

bool CreatetSRVfromFile(
	const T_Char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11ShaderResourceView** srv);

std::string ExtractExtension(std::string fullpath);
std::string ExtractFileName(std::string fullpath, char split);
