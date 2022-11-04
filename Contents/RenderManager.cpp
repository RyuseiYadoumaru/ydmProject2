//*****************************************************************************
//* @file   RenderManager.cpp
//* @brief  
//* @note   �`��̃R���|�[�l���g�̊Ǘ��ƃE�B���h�E�̕`���S������
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "RenderManager.h"
#include "../System/DirectXGraphics.h"

USING_SYSTEMS;

void GAME_SYSTEMS::RenderManager::ClearRenderer(myMath::Color& displayColor)
{
	/****	�^�[�Q�b�g�o�b�t�@�N���A	****/
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	ID3D11RenderTargetView& renderTargetView = DirectXGraphics::GetInstance()->GetRenderTargetView();
	deviceContext.ClearRenderTargetView(&renderTargetView, displayColor.GetFloat());

	/****	Z�o�b�t�@�N���A		****/
	ID3D11DepthStencilView& depthStencil = DirectXGraphics::GetInstance()->GetDepthStencilView();
	deviceContext.ClearDepthStencilView(&depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void GAME_SYSTEMS::RenderManager::SwapRenderBuffer()
{
	IDXGISwapChain& swapChain = DirectXGraphics::GetInstance()->GetSwapChain();
	swapChain.Present(0, 0);
}
