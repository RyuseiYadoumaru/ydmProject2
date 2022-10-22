//******************************************************************************
//* @file   DirectXGraphics.cpp
//* @brief  ダイレクトグラフィックス
//* @note   DirectX11のグラフィック周りのセットアップを行う
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************

#include "DirectXGraphics.h"
#include "Window.h"
#include "Debug.h"


//==============================================================================
//!	@fn		SetUp
//!	@brief	初期化
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::DirectXGraphics::SetUp()
{
	HRESULT	hr = S_OK;
	DXGI_MODE_DESC* displayModeList;

	/****	バックバッファ取得	****/
	m_backBufferWidth = systems::Window::GetInstance()->GetScreenSize().x;
	m_backBufferHeight = systems::Window::GetInstance()->GetScreenSize().y;

	/****	ドライバの種類	****/
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,		// Windows Advanced Rasterizer
		D3D_DRIVER_TYPE_REFERENCE,
	};
	uInt32 numDriverTypes = ARRAYSIZE(driverTypes);


#ifdef  _DEBUG
	uInt32 createDeviceFlags = 0;
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#else
	uInt32 createDeviceFlags = 0;
#endif

	/****	機能レベル	****/
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,					// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,					// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1					// Direct9.1対応GPUレベル
	};
	uInt32 numFeatureLevels = ARRAYSIZE(featureLevels);

	/****	DirectXグラフィックファクトリ-	****/
	IDXGIFactory* factory;			// factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr))
	{
		tools::Debug::LogError("DirectXグラフィックスインターフェース作成失敗");
		return false;
	}
	tools::Debug::Log("DirectXグラフィックスインターフェース作成成功");


	/****	アダプター作成	****/
	//ファクトリを使用して、
	//プライマリグラフィックインターフェイス（ビデオカード）のアダプタを作成します
	IDXGIAdapter* adapter;			// videocard
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr))
	{
		tools::Debug::LogError("ビデオカード用アダプターの列挙に失敗");
		return false;
	}
	tools::Debug::Log("ビデオカード用アダプターの列挙に成功");


	/****	アダプター出力作成	***/
	//プライマリアダプタの出力（モニター）を列挙します
	IDXGIOutput* adapterOutput;		// monitor
	uInt32 numModes = 0;
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr))
	{
		tools::Debug::LogError("ビデオカード用アダプター出力の列挙に失敗");
		return false;
	}
	tools::Debug::Log("ビデオカード用アダプター出力の列挙に成功");

	//アダプタ出力（モニター）のDXGI_FORMAT_R8G8B8_UNORM表示形式に適合するモードの数を取得します
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))
	{
		tools::Debug::LogError("アダプター出力のモード数取得に失敗");
		return false;
	}
	tools::Debug::Log("アダプター出力のモード数取得に成功");
	//モニター/ビデオカードの組み合わせで可能なすべての表示モードを保持するリストを作成します
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (displayModeList == nullptr)
	{
		tools::Debug::LogError("ディスプレイモードのリスト生成に失敗");
		return false;
	}
	tools::Debug::Log("ディスプレイモードのリスト生成に成功");

	//表示モードリストの構造を埋めます
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr))
	{
		tools::Debug::LogError("ディスプレイモードのリスト入力に失敗");
		return false;
	}
	tools::Debug::Log("ディスプレイモードのリスト入力に成功");


	/****	リフレッシュレート取得	****/
	uInt32 numerator = 60;			// 分子
	uInt32 denominator = 1;			// 分母
	//ここで、すべての表示モードを調べて、画面の幅と高さに一致するものを見つけます
	//一致するものが見つかったら、そのモニターのリフレッシュレートの分子と分母を保存します
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == m_backBufferWidth)
		{
			if (displayModeList[i].Height == m_backBufferHeight)
			{
				//リフレッシュレート保存
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	/****	初期化解放	****/
	delete[] displayModeList;
	displayModeList = nullptr;

	adapterOutput->Release();
	adapterOutput = nullptr;

	adapter->Release();
	adapter = nullptr;

	factory->Release();
	factory = nullptr;


	/****	スワップチェイン設定	****/
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));														//ゼロクリア
	sd.BufferCount = 1;																	//バックバッファの数
	sd.BufferDesc.Width = m_backBufferWidth;											//バックバッファの幅
	sd.BufferDesc.Height = m_backBufferHeight;											//バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;									//バックバッファフォーマット(R,G,B 範囲０．０から１．０)
	sd.BufferDesc.RefreshRate.Numerator = numerator;									//リフレッシュレート（分母）
	sd.BufferDesc.RefreshRate.Denominator = denominator;								//リフレッシュレート（分子）
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;				//スキャンライン描画モード
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;								//スケーリング
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;									//バックバッファの使用方法
	sd.OutputWindow = Window::GetInstance()->GetHandle();								//関連付けるウインドウ
	sd.SampleDesc.Count = 1;															//マルチサンプルの数
	sd.SampleDesc.Quality = 0;															//マルチサンプルのクオリティ
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;											//スワップエフェクト設定
	sd.Windowed = (Window::GetInstance()->GetWindowMode() != Window::Mode::Full_Screen);//フルスクリーン設定
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;									//モードの自動切り替え


	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					//ディスプレイデバイスのアダプタ（nullの場合最初に見つかったアダプタ）
			m_driverType,			//デバイスドライバのタイプ
			NULL,					//ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,		//デバイスフラグ
			featureLevels,			//機能レベル
			numFeatureLevels,		//機能レベル数
			D3D11_SDK_VERSION,		//
			&sd,					//スワップチェインの設定
			&m_swapChain,			//IDXGIDwapChainインタフェース	
			&m_device,				//ID3D11Deviceインタフェース
			&m_featureLevel,		//サポートされている機能レベル
			&m_immediateContext);	//デバイスコンテキスト
		if (SUCCEEDED(hr)) break;
	}
	if (FAILED(hr))
	{
		tools::Debug::LogError("スワップチェインの生成に失敗");
		return false;
	}
	tools::Debug::Log("スワップチェインの生成に成功");


	/****	レンダリングターゲット作成	****/
	// バックバッファのポインタを取得
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) return false;

	// バックバッファのポインタを指定してレンダーターゲットビューを作成
	hr = m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_renderTargetView);
	pBackBuffer->Release();
	pBackBuffer = nullptr;
	if (FAILED(hr)) return false;

	/****	Zバッファ設定	****/
	D3D11_TEXTURE2D_DESC depthBufferDesc;

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Width = m_backBufferWidth;
	depthBufferDesc.Height = m_backBufferHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	hr = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if (FAILED(hr))
	{
		tools::Debug::LogError("レンダリングターゲット作成に失敗");
		return false;
	}
	tools::Debug::Log("レンダリングターゲット作成に成功");


	/****	ステンシルステート作成	****/
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//ステンシルステート設定
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//ピクセルが前面にあるときのステンシル操作
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//ピクセルが後面にあるときのステンシル操作
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// ステンシルステート生成
	hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("ステンシルステート生成失敗");
		return false;
	}
	// デバイスコンテキストへセット
	m_immediateContext->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
	tools::Debug::Log("ステンシルステート生成成功");


	/****	深度ステンシルビュー初期化	****/
	//深度ステンシルビュー設定
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// 深度ステンシルビュー生成
	hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), &depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(hr))
	{
		tools::Debug::LogError("深度ステンシルビュー生成失敗");
		return false;
	}
	//レンダーターゲットビューと深度ステンシルバッファを出力レンダーパイプラインにバインド
	m_immediateContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	tools::Debug::Log("深度ステンシルビュー生成成功");


	/****	ラスター設定	****/
	//ポリゴンをどのように描画するかを設定します
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	//ラスタライザステート作成
	hr = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(hr))
	{
		return false;
	}

	//ラスタライザステートをセット
	m_immediateContext->RSSetState(m_rasterState.Get());


	/****	ビューポート設定	****/
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m_backBufferWidth;
	vp.Height = (FLOAT)m_backBufferHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_immediateContext->RSSetViewports(1, &vp);


	/****	ブレンドステート初期化	****/
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	//ブレンドステート設定
	blendStateDescription.RenderTarget[0].BlendEnable = true;						//ブレンディング有効
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;			//ピクセルシェーダーの値調整
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	//ピクセルシェーダーの実行操作
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;				//SrcBlend操作とDestBlend操作を組み合わせる
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;			//ピクセルシェーダーが出力するアルファ値に対して実行する操作
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;		//アルファ値に対して実行する操作
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;		//SrcBlendAlpha操作とDestBlendAlpha操作を組み合わせる
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;				//書き込みマスク

	//ブレンドステート作成
	hr = m_device->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("ブレンドステート生成失敗");
		return false;
	}

	//ブレンドステート作成（アルファブレンド不可）
	blendStateDescription.RenderTarget[0].BlendEnable = false;
	//ブレンドステート作成
	hr = m_device->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("ブレンドステート生成失敗");
		return false;
	}
	tools::Debug::Log("ブレンドステート生成成功");


	/****	サンプラーステート初期化	****/
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// サンプラーステート生成
	hr = m_device->CreateSamplerState(&smpDesc, &m_samplerState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("サンプラーステート生成失敗");
		return false;
	}
	// サンプラーステートを転送
	m_immediateContext->PSSetSamplers(0, 1, &m_samplerState);
	tools::Debug::Log("サンプラーステート生成成功");

	return true;
}


//==============================================================================
//!	@fn		ShutDown
//!	@brief	終了処理
//!	@note	シングルトンクラスの終了を明示的に行う
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//==============================================================================
bool systems::DirectXGraphics::ShutDown()
{
	if (m_immediateContext != nullptr) m_immediateContext->ClearState();
	if (m_swapChain != nullptr) m_swapChain->SetFullscreenState(false, nullptr);
	return true;
}
