#include "PixelShader.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"
#include "../System/MessageWindow.h"

bool GAME_SYSTEMS::PixelShader::LoadShader(T_String psFilePath)
{
	ID3D11Device& device = systems::DirectXGraphics::GetInstance()->GetDevice();

	// ピクセルシェーダーを生成
	bool sts = CreatePixelShader(			// ピクセルシェーダーオブジェクトを生成
		&device,		// デバイスオブジェクト
		psFilePath.c_str(),
		"main",
		"ps_5_0",
		&this->m_pixelShader);
	if (sts == false) 
	{
		systems::MessageWindow::GetInstance()->Error(TEXT("CreatePixelShader error"));
		return false;
	}
	return true;
}

void GAME_SYSTEMS::PixelShader::Releace()
{
	if (m_pixelShader != nullptr)
	{
		m_pixelShader->Release();
		m_pixelShader = nullptr;
	}
}

void GAME_SYSTEMS::PixelShader::BindShader()
{
	// デバイスコンテキスト
	ID3D11DeviceContext& devcontext = systems::DirectXGraphics::GetInstance()->GetImmediateContext();
	// ピクセルシェーダーをセット
	devcontext.PSSetShader(m_pixelShader.Get(), nullptr, 0);
}
