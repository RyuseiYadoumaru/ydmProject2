//******************************************************************************
//* @file   DirectXGraphics.h
//* @brief  �_�C���N�g�O���t�B�b�N�X
//* @note   DirectX11�̃O���t�B�b�N����̃Z�b�g�A�b�v���s��
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "SubSystem.h"
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

		//Z�o�b�t�@������
		void TurnOffZbuffer()
		{
			ID3D11RenderTargetView* rtvtable[1];

			rtvtable[0] = m_renderTargetView.Get();

			m_immediateContext->OMSetRenderTargets(
				1,										// �^�[�Q�b�g
				rtvtable,								// �r���[�e�[�u��
				nullptr									// �[�x�o�b�t�@�Ȃ�
			);
		}

		// Z�o�b�t�@�L����
		void TurnOnZBuffer() {
			ID3D11RenderTargetView* rtvtable[1];

			rtvtable[0] = m_renderTargetView.Get();

			m_immediateContext->OMSetRenderTargets(
				1,										// �^�[�Q�b�g
				rtvtable,								// �r���[�e�[�u��
				m_depthStencilView.Get()				// �[�x�o�b�t�@�Ȃ�
			);
		}

		ID3D11Device& GetDevice() const { return *m_device.Get(); }
		ID3D11DeviceContext& GetImmediateContext() const { return *m_immediateContext.Get(); }
		IDXGISwapChain& GetSwapChain() const { return *m_swapChain.Get(); }
		ID3D11RenderTargetView& GetRenderTargetView() const { return *m_renderTargetView.Get(); }
		ID3D11DepthStencilView& GetDepthStencilView() const { return *m_depthStencilView.Get(); }


	private:
		ComPtr<ID3D11Device>			m_device;						//DIRECT3DDEVICE11�f�o�C�X
		ComPtr<ID3D11DeviceContext>		m_immediateContext;				//DIRECT3DDEVICE11�f�o�C�X�R���e�L�X�g
		ComPtr<IDXGISwapChain>			m_swapChain;					//�X���b�v�`�F�C��

		ComPtr<ID3D11RenderTargetView>	m_renderTargetView;				//�����_�[�^�[�Q�b�g�r���[
		ComPtr<ID3D11Texture2D>			m_depthStencilBuffer;			//�y�o�b�t�@�A�X�e���V���o�b�t�@
		ComPtr<ID3D11DepthStencilState>	m_depthStencilState;			//�y�o�b�t�@�A�X�e���V���X�e�[�g
		ComPtr<ID3D11DepthStencilView>	m_depthStencilView;				//�y�o�b�t�@�A�X�e���V���r���[
		ComPtr<ID3D11RasterizerState>	m_rasterState;					//���X�^�[�X�e�[�^�X

		D3D_DRIVER_TYPE					m_driverType;					//�h���C�o�^�C�v
		D3D_FEATURE_LEVEL				m_featureLevel;					//�@�\���x��

		ComPtr<ID3D11BlendState>		m_alphaEnableBlendingState;		//�A���t�@�u�����h�X�e�[�g�i�L���j
		ComPtr<ID3D11BlendState>		m_alphaDisableBlendingState;	//�A���t�@�u�����h�X�e�[�g�i�����j

		ComPtr<ID3D11SamplerState>		m_samplerState;					//�T���v���[�X�e�[�g

		uInt32							m_backBufferWidth;				//�o�b�N�o�b�t�@X�T�C�Y
		uInt32							m_backBufferHeight;				//�o�b�N�o�b�t�@Y�T�C�Y

	};
}