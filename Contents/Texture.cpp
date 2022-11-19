#include "Texture.h"

#include "../System/MessageWindow.h"
#include "../System/Shader.h"
#include "../System/DirectxGraphics.h"

USING_SYSTEMS;

void GAME_SYSTEMS::Texture::Load(T_String fileName)
{
	bool sts = CreatetSRVfromFile(
		fileName.c_str(),
		&DirectXGraphics::GetInstance()->GetDevice(),
		&DirectXGraphics::GetInstance()->GetImmediateContext(),
		m_srv.GetAddressOf());

	if (sts == false)
	{
		MessageWindow::GetInstance()->Error(fileName + TEXT("Load Error"));
		return;
	}

}

void GAME_SYSTEMS::Texture::BindTexture(uInt32 registerIndex)
{
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	deviceContext.PSSetShaderResources(registerIndex, 1, m_srv.GetAddressOf());

}

void GAME_SYSTEMS::Texture::Releace()
{
	if (m_srv != nullptr)
	{
		m_srv->Release();
		m_srv = nullptr;
	}
}

