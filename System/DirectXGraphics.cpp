//******************************************************************************
//* @file   DirectXGraphics.cpp
//* @brief  �_�C���N�g�O���t�B�b�N�X
//* @note   DirectX11�̃O���t�B�b�N����̃Z�b�g�A�b�v���s��
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************

#include "DirectXGraphics.h"
#include "Window.h"
#include "Debug.h"


//==============================================================================
//!	@fn		SetUp
//!	@brief	������
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::DirectXGraphics::SetUp()
{
	HRESULT	hr = S_OK;
	DXGI_MODE_DESC* displayModeList;

	/****	�o�b�N�o�b�t�@�擾	****/
	m_backBufferWidth = systems::Window::GetInstance()->GetScreenSize().x;
	m_backBufferHeight = systems::Window::GetInstance()->GetScreenSize().y;

	/****	�h���C�o�̎��	****/
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

	/****	�@�\���x��	****/
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,					// DirectX11�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_0,					// DirectX10�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_1					// Direct9.1�Ή�GPU���x��
	};
	uInt32 numFeatureLevels = ARRAYSIZE(featureLevels);

	/****	DirectX�O���t�B�b�N�t�@�N�g��-	****/
	IDXGIFactory* factory;			// factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr))
	{
		tools::Debug::LogError("DirectX�O���t�B�b�N�X�C���^�[�t�F�[�X�쐬���s");
		return false;
	}
	tools::Debug::Log("DirectX�O���t�B�b�N�X�C���^�[�t�F�[�X�쐬����");


	/****	�A�_�v�^�[�쐬	****/
	//�t�@�N�g�����g�p���āA
	//�v���C�}���O���t�B�b�N�C���^�[�t�F�C�X�i�r�f�I�J�[�h�j�̃A�_�v�^���쐬���܂�
	IDXGIAdapter* adapter;			// videocard
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�r�f�I�J�[�h�p�A�_�v�^�[�̗񋓂Ɏ��s");
		return false;
	}
	tools::Debug::Log("�r�f�I�J�[�h�p�A�_�v�^�[�̗񋓂ɐ���");


	/****	�A�_�v�^�[�o�͍쐬	***/
	//�v���C�}���A�_�v�^�̏o�́i���j�^�[�j��񋓂��܂�
	IDXGIOutput* adapterOutput;		// monitor
	uInt32 numModes = 0;
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�r�f�I�J�[�h�p�A�_�v�^�[�o�̗͂񋓂Ɏ��s");
		return false;
	}
	tools::Debug::Log("�r�f�I�J�[�h�p�A�_�v�^�[�o�̗͂񋓂ɐ���");

	//�A�_�v�^�o�́i���j�^�[�j��DXGI_FORMAT_R8G8B8_UNORM�\���`���ɓK�����郂�[�h�̐����擾���܂�
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�A�_�v�^�[�o�͂̃��[�h���擾�Ɏ��s");
		return false;
	}
	tools::Debug::Log("�A�_�v�^�[�o�͂̃��[�h���擾�ɐ���");
	//���j�^�[/�r�f�I�J�[�h�̑g�ݍ��킹�ŉ\�Ȃ��ׂĂ̕\�����[�h��ێ����郊�X�g���쐬���܂�
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (displayModeList == nullptr)
	{
		tools::Debug::LogError("�f�B�X�v���C���[�h�̃��X�g�����Ɏ��s");
		return false;
	}
	tools::Debug::Log("�f�B�X�v���C���[�h�̃��X�g�����ɐ���");

	//�\�����[�h���X�g�̍\���𖄂߂܂�
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�f�B�X�v���C���[�h�̃��X�g���͂Ɏ��s");
		return false;
	}
	tools::Debug::Log("�f�B�X�v���C���[�h�̃��X�g���͂ɐ���");


	/****	���t���b�V�����[�g�擾	****/
	uInt32 numerator = 60;			// ���q
	uInt32 denominator = 1;			// ����
	//�����ŁA���ׂĂ̕\�����[�h�𒲂ׂāA��ʂ̕��ƍ����Ɉ�v������̂������܂�
	//��v������̂�����������A���̃��j�^�[�̃��t���b�V�����[�g�̕��q�ƕ����ۑ����܂�
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == m_backBufferWidth)
		{
			if (displayModeList[i].Height == m_backBufferHeight)
			{
				//���t���b�V�����[�g�ۑ�
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	/****	���������	****/
	delete[] displayModeList;
	displayModeList = nullptr;

	adapterOutput->Release();
	adapterOutput = nullptr;

	adapter->Release();
	adapter = nullptr;

	factory->Release();
	factory = nullptr;


	/****	�X���b�v�`�F�C���ݒ�	****/
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));														//�[���N���A
	sd.BufferCount = 1;																	//�o�b�N�o�b�t�@�̐�
	sd.BufferDesc.Width = m_backBufferWidth;											//�o�b�N�o�b�t�@�̕�
	sd.BufferDesc.Height = m_backBufferHeight;											//�o�b�N�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;									//�o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B �͈͂O�D�O����P�D�O)
	sd.BufferDesc.RefreshRate.Numerator = numerator;									//���t���b�V�����[�g�i����j
	sd.BufferDesc.RefreshRate.Denominator = denominator;								//���t���b�V�����[�g�i���q�j
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;				//�X�L�������C���`�惂�[�h
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;								//�X�P�[�����O
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;									//�o�b�N�o�b�t�@�̎g�p���@
	sd.OutputWindow = Window::GetInstance()->GetHandle();								//�֘A�t����E�C���h�E
	sd.SampleDesc.Count = 1;															//�}���`�T���v���̐�
	sd.SampleDesc.Quality = 0;															//�}���`�T���v���̃N�I���e�B
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;											//�X���b�v�G�t�F�N�g�ݒ�
	sd.Windowed = (Window::GetInstance()->GetWindowMode() != Window::Mode::Full_Screen);//�t���X�N���[���ݒ�
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;									//���[�h�̎����؂�ւ�


	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					//�f�B�X�v���C�f�o�C�X�̃A�_�v�^�inull�̏ꍇ�ŏ��Ɍ��������A�_�v�^�j
			m_driverType,			//�f�o�C�X�h���C�o�̃^�C�v
			NULL,					//�\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�Ɏw�肷��
			createDeviceFlags,		//�f�o�C�X�t���O
			featureLevels,			//�@�\���x��
			numFeatureLevels,		//�@�\���x����
			D3D11_SDK_VERSION,		//
			&sd,					//�X���b�v�`�F�C���̐ݒ�
			&m_swapChain,			//IDXGIDwapChain�C���^�t�F�[�X	
			&m_device,				//ID3D11Device�C���^�t�F�[�X
			&m_featureLevel,		//�T�|�[�g����Ă���@�\���x��
			&m_immediateContext);	//�f�o�C�X�R���e�L�X�g
		if (SUCCEEDED(hr)) break;
	}
	if (FAILED(hr))
	{
		tools::Debug::LogError("�X���b�v�`�F�C���̐����Ɏ��s");
		return false;
	}
	tools::Debug::Log("�X���b�v�`�F�C���̐����ɐ���");


	/****	�����_�����O�^�[�Q�b�g�쐬	****/
	// �o�b�N�o�b�t�@�̃|�C���^���擾
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) return false;

	// �o�b�N�o�b�t�@�̃|�C���^���w�肵�ă����_�[�^�[�Q�b�g�r���[���쐬
	hr = m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_renderTargetView);
	pBackBuffer->Release();
	pBackBuffer = nullptr;
	if (FAILED(hr)) return false;

	/****	Z�o�b�t�@�ݒ�	****/
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
		tools::Debug::LogError("�����_�����O�^�[�Q�b�g�쐬�Ɏ��s");
		return false;
	}
	tools::Debug::Log("�����_�����O�^�[�Q�b�g�쐬�ɐ���");


	/****	�X�e���V���X�e�[�g�쐬	****/
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//�X�e���V���X�e�[�g�ݒ�
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//�s�N�Z�����O�ʂɂ���Ƃ��̃X�e���V������
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//�s�N�Z������ʂɂ���Ƃ��̃X�e���V������
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// �X�e���V���X�e�[�g����
	hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�X�e���V���X�e�[�g�������s");
		return false;
	}
	// �f�o�C�X�R���e�L�X�g�փZ�b�g
	m_immediateContext->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
	tools::Debug::Log("�X�e���V���X�e�[�g��������");


	/****	�[�x�X�e���V���r���[������	****/
	//�[�x�X�e���V���r���[�ݒ�
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// �[�x�X�e���V���r���[����
	hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), &depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�[�x�X�e���V���r���[�������s");
		return false;
	}
	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���o�b�t�@���o�̓����_�[�p�C�v���C���Ƀo�C���h
	m_immediateContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	tools::Debug::Log("�[�x�X�e���V���r���[��������");


	/****	���X�^�[�ݒ�	****/
	//�|���S�����ǂ̂悤�ɕ`�悷�邩��ݒ肵�܂�
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

	//���X�^���C�U�X�e�[�g�쐬
	hr = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(hr))
	{
		return false;
	}

	//���X�^���C�U�X�e�[�g���Z�b�g
	m_immediateContext->RSSetState(m_rasterState.Get());


	/****	�r���[�|�[�g�ݒ�	****/
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m_backBufferWidth;
	vp.Height = (FLOAT)m_backBufferHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_immediateContext->RSSetViewports(1, &vp);


	/****	�u�����h�X�e�[�g������	****/
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	//�u�����h�X�e�[�g�ݒ�
	blendStateDescription.RenderTarget[0].BlendEnable = true;						//�u�����f�B���O�L��
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;			//�s�N�Z���V�F�[�_�[�̒l����
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	//�s�N�Z���V�F�[�_�[�̎��s����
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;				//SrcBlend�����DestBlend�����g�ݍ��킹��
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;			//�s�N�Z���V�F�[�_�[���o�͂���A���t�@�l�ɑ΂��Ď��s���鑀��
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;		//�A���t�@�l�ɑ΂��Ď��s���鑀��
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;		//SrcBlendAlpha�����DestBlendAlpha�����g�ݍ��킹��
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;				//�������݃}�X�N

	//�u�����h�X�e�[�g�쐬
	hr = m_device->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�u�����h�X�e�[�g�������s");
		return false;
	}

	//�u�����h�X�e�[�g�쐬�i�A���t�@�u�����h�s�j
	blendStateDescription.RenderTarget[0].BlendEnable = false;
	//�u�����h�X�e�[�g�쐬
	hr = m_device->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�u�����h�X�e�[�g�������s");
		return false;
	}
	tools::Debug::Log("�u�����h�X�e�[�g��������");


	/****	�T���v���[�X�e�[�g������	****/
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// �T���v���[�X�e�[�g����
	hr = m_device->CreateSamplerState(&smpDesc, &m_samplerState);
	if (FAILED(hr))
	{
		tools::Debug::LogError("�T���v���[�X�e�[�g�������s");
		return false;
	}
	// �T���v���[�X�e�[�g��]��
	m_immediateContext->PSSetSamplers(0, 1, &m_samplerState);
	tools::Debug::Log("�T���v���[�X�e�[�g��������");

	return true;
}


//==============================================================================
//!	@fn		ShutDown
//!	@brief	�I������
//!	@note	�V���O���g���N���X�̏I���𖾎��I�ɍs��
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//==============================================================================
bool systems::DirectXGraphics::ShutDown()
{
	if (m_immediateContext != nullptr) m_immediateContext->ClearState();
	if (m_swapChain != nullptr) m_swapChain->SetFullscreenState(false, nullptr);
	return true;
}
