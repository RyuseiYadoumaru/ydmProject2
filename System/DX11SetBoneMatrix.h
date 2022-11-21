//*****************************************************************************
//* @file   DX11SetBoneMatrix.h
//* @brief  
//* @note   ボーンに必要なデータを定数バッファにセットする
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
	class Skeleton;
}

namespace SYSTEMS
{
	class DX11SetBoneMatrix
	{
		SINGLETON_CLASS(DX11SetBoneMatrix);
	public:
		static constexpr uInt32 m_MaxBoneNum = 400;

	public:
		ALIGN16 struct  ConstantBufferBoneMatrix
		{
			DirectX::XMFLOAT4X4 BoneMatrix[m_MaxBoneNum];
		};

	public:
		bool Initialize();
		bool Finalize();
		void SetConstantBuffer(Vector<DirectX::XMFLOAT4X4>& matrixList);

	private:
		ComPtr<ID3D11Buffer> m_constantBufferBone = nullptr;
		ConstantBufferBoneMatrix m_cbBone;
	};
}
