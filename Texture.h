#pragma once
#include <d3d11.h>
#include <string>
#include "macro.h"
#include "std.h"

class Texture
{
public:
	bool Load(T_String fileName, T_String filepath);
	void SetTexture(int slotIndex);

private:
	ID3D11Resource* m_resource;
	ID3D11ShaderResourceView* m_srv; // SRV
};