//*****************************************************************************
//* @file   DX11SetMaterial.h
//* @brief  
//* @note   �}�e���A���ɕK�v�ȃf�[�^��萔�o�b�t�@�ɃZ�b�g����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "Shader.h"
#include "DirectXGraphics.h"
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class Material;
}

namespace SYSTEMS
{
	class DX11SetMaterial
	{
		SINGLETON_CLASS(DX11SetMaterial);

	public:
		ALIGN16 struct  ConstantBufferMaterial
		{
			DirectX::XMFLOAT4 AmbientColor  = { 0.0f, 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT4 DiffuseColor  = { 0.0f, 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT4 SpecularColor = { 0.0f, 0.0f, 0.0f, 0.0f };
		};

	public:
		bool Initialize();
		bool Finalize();
		void SetConstantBuffer(const GAME_SYSTEMS::Material& material);

	private:
		ComPtr<ID3D11Buffer> m_constantBufferMaterial = nullptr;
		ConstantBufferMaterial m_cbMaterial;
	};
}
