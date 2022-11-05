//******************************************************************************
//* @file   Shader.cpp
//* @brief  
//* @note   シェーダー周りの読み込みを行う
//* 
//* @author YadoumaruRyusei
//* @date   December 2021
//*****************************************************************************
#include	"Shader.h"
#include "MessageWindow.h"


USING_SYSTEMS;


// 拡張子を取得する
T_String ExtractExtension(T_String fullpath) 
{
	size_t ext_i = fullpath.find_last_of(TEXT("."));
	T_String extname = fullpath.substr(ext_i+1, fullpath.size() - ext_i);
	return extname;
}

T_String ExtractFileName(T_String fullpath, char split)
{
	unsigned int path_i = static_cast<unsigned int>(fullpath.find_last_of(split) + 1);//7
	unsigned int ext_i = static_cast<unsigned int>(fullpath.find_last_of(TEXT(".")));//10
	T_String pathname = fullpath.substr(0, path_i + 1);//0文字目から７文字切り出す TEXT("C:\\aaa\\"
	T_String extname = fullpath.substr(ext_i, fullpath.size() - ext_i); // 10文字目から４文字切り出す ".txt"
	T_String filename = fullpath.substr(path_i, ext_i - path_i);//

	return filename + extname;
}

//--------------------------------------------------------------------------------------
// シェーダーをコンパイル
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const T_Char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	ID3DBlob* p1 = nullptr;

	HRESULT hr = S_OK;

	WCHAR	filename[512];
	size_t 	wLen = 0;
	int err = 0;

#ifdef _UNICODE
	lstrcpyW(filename, szFileName);
#else
	// char -> wcharに変換
	setlocale(LC_ALL, "japanese");
	err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);
#endif // _UNICODE

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(
		filename,							// filename LPCWST pFileName
		nullptr,							// D3D_SHADER_MACRO *pDefines
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// ID3DInclude *pInclude
		szEntryPoint,						// LPCSTR pEntrypoint
		szShaderModel,						// LPCSTR pTarget
		dwShaderFlags,						// UINT Flags1
		0,									// UINT Flags2
		ppBlobOut,							// ID3DBlob** ppCode
		&pErrorBlob);						// ID3DBlob** ppErrorMsg 
	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr)
		{
			MessageBox(NULL,
				(T_Char*)pErrorBlob->GetBufferPointer(), TEXT("Error"), MB_OK);
		}
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// 頂点シェーダーオブジェクトを生成する
//--------------------------------------------------------------------------------------
bool CreateVertexShader(ID3D11Device* device,
						const T_Char* szFileName, 
						LPCSTR szEntryPoint, 
						LPCSTR szShaderModel,
						D3D11_INPUT_ELEMENT_DESC* layout,
						unsigned int numElements,
						ID3D11VertexShader** ppVertexShader,
						ID3D11InputLayout**  ppVertexLayout){

	ID3DBlob* pBlob=nullptr;

	HRESULT hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, &pBlob);
	if (FAILED(hr)){
		return false;
	}

	// 頂点シェーダーを生成
	hr = device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, ppVertexShader);
	if (FAILED(hr))
	{
		pBlob->Release();
		return false;
	}

	// 頂点データ定義生成
	hr = device->CreateInputLayout(
		layout,
		numElements,
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		ppVertexLayout);

	if (FAILED(hr)){
		MessageBox(nullptr,TEXT("CreateInputLayout error"), TEXT("error"), MB_OK);
		pBlob->Release();
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーオブジェクトを生成する
//--------------------------------------------------------------------------------------
bool CreatePixelShader(ID3D11Device* device,
	const T_Char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3D11PixelShader** ppPixelShader){

	ID3DBlob* pBlob = nullptr;

	// コンパイル
	HRESULT hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, &pBlob);
	if (FAILED(hr)){
		return false;
	}

	// 頂点シェーダーを生成
	hr = device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, ppPixelShader);
	if (FAILED(hr))
	{
		pBlob->Release();
		return false;
	}

	return true;
}

/*----------------------------
コンスタントバッファを作成
------------------------------*/
bool CreateConstantBuffer(
	ID3D11Device* device,					// デバイスオブジェクト
	unsigned int bytesize,					// コンスタントバッファサイズ
	ID3D11Buffer** pConstantBuffer			// コンスタントバッファ
	){

	// コンスタントバッファ生成
	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// バッファ使用方法
	bd.ByteWidth = bytesize;									// バッファの大き
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;					// コンスタントバッファ
	bd.CPUAccessFlags = 0;										// CPUアクセス不要

	HRESULT hr = device->CreateBuffer(&bd, nullptr, pConstantBuffer);
	if (FAILED(hr)){
		MessageBox(nullptr, TEXT("CreateBuffer(constant buffer) error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*----------------------------
コンスタントバッファを作成
------------------------------*/
bool CreateConstantBufferWrite(
	ID3D11Device* device,					// デバイスオブジェクト
	unsigned int bytesize,					// コンスタントバッファサイズ
	ID3D11Buffer** pConstantBuffer			// コンスタントバッファ
) {

	// コンスタントバッファ生成
	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;							// バッファ使用方法
	bd.ByteWidth = bytesize;									// バッファの大き
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;					// コンスタントバッファ
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;					// CPUアクセス可能

	HRESULT hr = device->CreateBuffer(&bd, nullptr, pConstantBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("CreateBuffer(constant buffer) error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------
インデックスバッファを作成
--------------------------*/
bool CreateIndexBuffer(
	ID3D11Device* device,						// デバイスオブジェクト
	unsigned int indexnum,						// インデックス数
	void* indexdata,							// インデックスデータ格納メモリ先頭アドレス
	ID3D11Buffer** pIndexBuffer){				// インデックスバッファ

	// インデックスバッファ生成
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// バッファ使用方
	bd.ByteWidth = sizeof(unsigned int) * indexnum;				// バッファの大き
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;						// インデックスバッファ
	bd.CPUAccessFlags = 0;										// CPUアクセス不要

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indexdata;

	HRESULT hr = device->CreateBuffer(&bd, &InitData, pIndexBuffer);
	if (FAILED(hr)){
		MessageBox(nullptr, TEXT("CreateBuffer(index buffer) error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------
頂点バッファを作成
--------------------------*/
bool CreateVertexBuffer(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
	){

	HRESULT hr;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;							// バッファ使用方法
	bd.ByteWidth = stride * vertexnum;						// バッファの大きさ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファ
	bd.CPUAccessFlags = 0;									// CPUアクセス不要

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertexdata;							// バッファの初期値

	hr = device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// バッファ生成
	if (FAILED(hr)){
		MessageBox(nullptr, TEXT("CreateBuffer(vertex buffer) error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------
頂点バッファを作成(ＣＰＵ書き込み可能)
--------------------------*/
bool CreateVertexBufferWrite(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
) {

	HRESULT hr;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;							// バッファ使用方法
	bd.ByteWidth = stride * vertexnum;						// バッファの大きさ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファ
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				// CPUアクセス可能

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertexdata;							// バッファの初期値

	hr = device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// バッファ生成
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("CreateBuffer(vertex buffer) error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------
頂点バッファ(UAV)を作成
--------------------------*/
bool CreateVertexBufferUAV(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
	){

	HRESULT hr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = stride * vertexnum;						// バッファの大きさ
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags =
		D3D11_BIND_VERTEX_BUFFER |
		D3D11_BIND_SHADER_RESOURCE |
		D3D11_BIND_UNORDERED_ACCESS;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertexdata;							// バッファの初期値

	hr = device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// バッファ生成
	if (FAILED(hr)){
		MessageBox(nullptr, TEXT("CreateBuffer(vertex buffer) error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------
 Structuredバッファを作成
--------------------------*/
bool CreateStructuredBuffer(
	ID3D11Device* device,
	unsigned int stride,				// ストライドバイト数
	unsigned int num,					// 個数
	void* data,							// データ格納メモリ先頭アドレス
	ID3D11Buffer** pStructuredBuffer	// RWStructuredBuffer
	){

	HRESULT hr;

	// Structuredバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;		// UAバッファ
	bd.ByteWidth = stride * num;													// バッファの大きさ
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;							// RWStructuredBuffer
	bd.StructureByteStride = stride;												// 構造化バッファサイズ
	bd.CPUAccessFlags = 0;															// CPUアクセス不要

	if (data != nullptr){
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));

		InitData.pSysMem = data;							// バッファの初期値

		hr = device->CreateBuffer(&bd, &InitData, pStructuredBuffer);		// バッファ生成
	}
	else{
		hr = device->CreateBuffer(&bd, nullptr, pStructuredBuffer);		// バッファ生成
	}
	if (FAILED(hr)){
		MessageBox(nullptr, TEXT("CreateBuffer(StructuredBuffer) error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*---------------------------------
STAGINGバッファを作成しコピーする
----------------------------------*/
ID3D11Buffer* CreateAndCopyToBuffer(
	ID3D11Device* device,
	ID3D11DeviceContext* devicecontext,
	ID3D11Buffer* pBuffer	// RWStructuredBuffer
	){

	HRESULT hr;
	ID3D11Buffer* CloneBuffer = nullptr;

	// Structuredバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	pBuffer->GetDesc(&bd);

	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	bd.Usage = D3D11_USAGE_STAGING;
	bd.BindFlags = 0;
	bd.MiscFlags = 0;

	hr = device->CreateBuffer(&bd, nullptr, &CloneBuffer);
	if (SUCCEEDED(hr)){
		devicecontext->CopyResource(CloneBuffer, pBuffer);
	}

	return CloneBuffer;
}
/*------------------------
ShaderResourceViewを作成
--------------------------*/
bool CreateShaderResourceView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,	// Buffer
	ID3D11ShaderResourceView** ppSRV){

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	pBuffer->GetDesc(&bd);

	D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;

	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS){
		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / 4;
	}
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED){
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	else{
		return false;
	}

	HRESULT hr;
	hr = device->CreateShaderResourceView(pBuffer, &srvDesc, ppSRV);
	if (FAILED(hr)){
		MessageBox(nullptr, TEXT("CreateShaderResourceView error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------
UnOrderedAccessViewを作成
--------------------------*/
bool CreateUnOrderAccessView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,	// Buffer
	ID3D11UnorderedAccessView** ppUAV){

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	pBuffer->GetDesc(&bd);

	D3D11_UNORDERED_ACCESS_VIEW_DESC  uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;

	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS){
		uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		uavDesc.Buffer.NumElements = bd.ByteWidth / 4;
	}
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED){
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.Buffer.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	else{
		return false;
	}

	HRESULT hr;
	hr = device->CreateUnorderedAccessView(pBuffer, &uavDesc, ppUAV);
	if (FAILED(hr)){
		MessageBox(nullptr, TEXT("CreateUnorderedAccessView error"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------------------------------------------
　ＴＧＡファイルを読み込みシェーダーリソースビュー―を作成する
 --------------------------------------------------------------*/
bool CreatetSRVfromTGAFile(const T_Char* filename,
	ID3D11Device* device,
	ID3D11ShaderResourceView** srv){

	HRESULT		hr;

	wchar_t ws[512];
#ifdef _UNICODE
	lstrcpyW(ws, filename);
#else
	size_t ret;
	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);
#endif // _UNICODE


	DirectX::TexMetadata meta;
	DirectX::GetMetadataFromTGAFile(ws, meta);

	std::unique_ptr<DirectX::ScratchImage> image(new DirectX::ScratchImage);
	hr = LoadFromTGAFile(ws, &meta, *image);
	if (FAILED(hr)){
		//		MessageBox(nullptr, "Texture Load error"), "error"), MB_OK);
		return false;
	}

	// シェーダーリソースビュー作成
	hr = DirectX::CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), meta, srv);
	if (FAILED(hr)){
		//		MessageBox(nullptr, TEXT("CreateShaderResourceView error"), "error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------------------------------------------
　WICファイルを読み込みシェーダーリソースビュー―を作成する
 --------------------------------------------------------------*/
bool CreatetSRVfromWICFile(const T_Char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext*	device11Context,
	ID3D11ShaderResourceView** srv){

	ID3D11Resource*			texr = nullptr;		// テクスチャリソース

	wchar_t ws[512];

#ifdef _UNICODE
	lstrcpyW(ws, filename);
#else
	size_t ret;
	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);
#endif // _UNICODE

	// テクスチャ読み込み
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		device,
		device11Context,
		ws,
		&texr, srv);
	if (FAILED(hr)){
//		MessageBox(NULL, TEXT("CreateWICTextureFromFile", TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------------------------------------------
　DDSファイルを読み込みシェーダーリソースビュー―を作成する
 --------------------------------------------------------------*/
bool CreatetSRVfromDDS(const T_Char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext*	device11Context,
	ID3D11ShaderResourceView** srv) {

	ID3D11Resource*			texr = nullptr;		// テクスチャリソース

	wchar_t ws[512];

#ifdef _UNICODE
	lstrcpyW(ws, filename);
#else
	size_t ret;
	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);
#endif // _UNICODE


	// テクスチャ読み込み
	HRESULT hr = DirectX::CreateDDSTextureFromFile(
		device,
		device11Context,
		ws,
		&texr, srv);
	if (FAILED(hr)) {
		//		MessageBox(NULL, TEXT("CreateWICTextureFromFile", TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

/*------------------------------------------------------------
　ファイルを読み込みシェーダーリソースビューを作成する
 --------------------------------------------------------------*/
bool CreatetSRVfromFile(
	const T_Char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext*	device11Context,
	ID3D11ShaderResourceView** srv) {

	T_String fname(filename);

	T_String ext;

	// 拡張子を取得する
	ext = ExtractExtension(fname);

	// DDSファイル
	if (ext == TEXT("dds")) {
		bool sts = CreatetSRVfromDDS(fname.c_str(),
			device,
			device11Context,
			srv);
		if (!sts) {
			MessageBox(nullptr, fname.c_str(), TEXT("texload error"), MB_OK);
			return false;
		}
	}
	// TGAファイル
	else if (ext == TEXT("tga")) {
		bool sts = CreatetSRVfromTGAFile(fname.c_str(),
			device,
			srv);
		if (!sts) {
			MessageBox(nullptr, fname.c_str(), TEXT("texload error"), MB_OK);
			return false;
		}
	}
	// その他ファイル
	else {
		bool sts = CreatetSRVfromWICFile(fname.c_str(),
			device,
			device11Context,
			srv);
		if (!sts) {
			MessageBox(nullptr, fname.c_str(), TEXT("texload error"), MB_OK);
			return false;
		}
	}
	return true;
}