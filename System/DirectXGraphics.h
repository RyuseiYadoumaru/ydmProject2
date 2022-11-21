//******************************************************************************
//* @file   DirectXGraphics.h
//* @brief  ダイレクトグラフィックス
//* @note   DirectX11のグラフィック周りのセットアップを行う
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "Core/SubSystem.h"
#include "std.h"
#include "macro.h"
#include <d3d11.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;


namespace systems
{
	class DirectXGraphics final : public SubSystem
	{
		SINGLETON_CLASS(DirectXGraphics);
	public:
		bool SetUp()	override;
		bool ShutDown() override;

		void TurnOffAlphaBlending() { float blendFactor[4] = { 0.0f }; m_immediateContext->OMSetBlendState(m_alphaDisableBlendingState.Get(), blendFactor, 0xffffffff); }
		void TurnOnAlphaBlending() { float blendFactor[4] = { 0.0f }; m_immediateContext->OMSetBlendState(m_alphaEnableBlendingState.Get(), blendFactor, 0xffffffff); }

		//Zバッファ無効化
		void TurnOffZbuffer()
		{
			ID3D11RenderTargetView* rtvtable[1];

			rtvtable[0] = m_renderTargetView.Get();

			m_immediateContext->OMSetRenderTargets(
				1,										// ターゲット
				rtvtable,								// ビューテーブル
				nullptr									// 深度バッファなし
			);
		}

		// Zバッファ有効化
		void TurnOnZBuffer() {
			ID3D11RenderTargetView* rtvtable[1];

			rtvtable[0] = m_renderTargetView.Get();

			m_immediateContext->OMSetRenderTargets(
				1,										// ターゲット
				rtvtable,								// ビューテーブル
				m_depthStencilView.Get()				// 深度バッファなし
			);
		}

		ID3D11Device& GetDevice() const { return *m_device.Get(); }
		ID3D11DeviceContext& GetImmediateContext() const { return *m_immediateContext.Get(); }
		IDXGISwapChain& GetSwapChain() const { return *m_swapChain.Get(); }
		ID3D11RenderTargetView& GetRenderTargetView() const { return *m_renderTargetView.Get(); }
		ID3D11DepthStencilView& GetDepthStencilView() const { return *m_depthStencilView.Get(); }


	private:
		ComPtr<ID3D11Device>			m_device				= nullptr;	// DIRECT3DDEVICE11デバイス
		ComPtr<ID3D11DeviceContext>		m_immediateContext		= nullptr;	// DIRECT3DDEVICE11デバイスコンテキスト
		ComPtr<IDXGISwapChain>			m_swapChain				= nullptr;	// スワップチェイン

		ComPtr<ID3D11RenderTargetView>	m_renderTargetView		= nullptr;	// レンダーターゲットビュー
		ComPtr<ID3D11Texture2D>			m_depthStencilBuffer	= nullptr;	// Ｚバッファ、ステンシルバッファ
		ComPtr<ID3D11DepthStencilState>	m_depthStencilState		= nullptr;	// Ｚバッファ、ステンシルステート
		ComPtr<ID3D11DepthStencilView>	m_depthStencilView		= nullptr;	// Ｚバッファ、ステンシルビュー
		ComPtr<ID3D11RasterizerState>	m_rasterState			= nullptr;	// ラスターステータス

		D3D_DRIVER_TYPE					m_driverType			= D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_NULL;		// ドライバタイプ
		D3D_FEATURE_LEVEL				m_featureLevel			= D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;	// 機能レベル

		ComPtr<ID3D11BlendState>		m_alphaEnableBlendingState	= nullptr;	// アルファブレンドステート（有効）
		ComPtr<ID3D11BlendState>		m_alphaDisableBlendingState	= nullptr;	// アルファブレンドステート（無効）

		ComPtr<ID3D11SamplerState>		m_samplerState				= nullptr;	// サンプラーステート

		uInt32							m_backBufferWidth	= 0;				// バックバッファXサイズ
		uInt32							m_backBufferHeight	= 0;				// バックバッファYサイズ

	};
}