#include "Texture.h"
#include "System/Shader.h"
#include "System/DirectxGraphics.h"

USING_SYSTEMS;

bool Texture::Load(T_String fileName, T_String filepath)
{
	T_String name = filepath + "/" + fileName;

	bool sts = CreatetSRVfromFile(
		name.c_str(),
		&DirectXGraphics::GetInstance()->GetDevice(),
		&DirectXGraphics::GetInstance()->GetImmediateContext(),
		&this->m_srv);

	if (!sts) 
	{
		MessageBox(nullptr, (name + TEXT("load error")).c_str(), TEXT("error"), MB_OK);
		return false;
	}

	return true;
}

void Texture::SetTexture(int slotIndex)
{
	DirectXGraphics::GetInstance()->GetImmediateContext().PSSetShaderResources(slotIndex, 1, &this->m_srv);
}