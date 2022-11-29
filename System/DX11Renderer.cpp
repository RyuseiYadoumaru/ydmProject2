//*****************************************************************************
//* @file   RenderManager.cpp
//* @brief  
//* @note   描画のコンポーネントの管理とウィンドウの描画を担当する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "DX11Renderer.h"
#include "../System/DirectXGraphics.h"

void SYSTEMS::DX11Renderer::ClearRenderer()
{
	/****	ターゲットバッファクリア	****/
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	ID3D11RenderTargetView& renderTargetView = DirectXGraphics::GetInstance()->GetRenderTargetView();
	Float32 color[4] = { m_screenColor.x, m_screenColor.y, m_screenColor.z, 1.0f };
	deviceContext.ClearRenderTargetView(&renderTargetView, color);

	/****	Zバッファクリア		****/
	ID3D11DepthStencilView& depthStencil = DirectXGraphics::GetInstance()->GetDepthStencilView();
	deviceContext.ClearDepthStencilView(&depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void SYSTEMS::DX11Renderer::SwapRenderBuffer()
{
	IDXGISwapChain& swapChain = DirectXGraphics::GetInstance()->GetSwapChain();
	swapChain.Present(0, 0);
}
