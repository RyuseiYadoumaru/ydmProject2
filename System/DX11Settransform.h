//*****************************************************************************
//* @file   DX11Settransform.h
//* @brief  
//* @note   トランスフォームに必要なデータを定数バッファにセットする
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "Shader.h"
#include "DirectXGraphics.h"
#include "macro.h"
#include "std.h"

using namespace DirectX;

namespace SYSTEMS
{
	class DX11SetTransform
	{
		SINGLETON_CLASS(DX11SetTransform)

	public:
		static DX11SetTransform* Get()
		{
			static DX11SetTransform instance;
			return &instance;
		}

	public:
		// 定数バッファ定義(ワールド変換行列)
		ALIGN16 struct ConstantBufferWorld
		{
			XMMATRIX World;				// ワールド変換行列
		};
		// 定数バッファ定義(ビュー変換行列)
		ALIGN16 struct ConstantBufferView
		{
			XMMATRIX View;				// ビュー変換行列
		};
		// 定数バッファ定義(毎フレーム設定)
		ALIGN16 struct ConstantBufferProjection
		{
			XMMATRIX Projection;		// プロジェクション変換行列
		};

		enum class TYPE
		{
			WORLD,
			VIEW,
			PROJECTION
		};

		void Uninit()
		{
			if (m_pConstantBufferWorld)
			{
				m_pConstantBufferWorld->Release();
				m_pConstantBufferWorld = nullptr;
			}
			if (m_pConstantBufferView)
			{
				m_pConstantBufferView->Release();
				m_pConstantBufferView = nullptr;
			}
			if (m_pConstantBufferProjection)
			{
				m_pConstantBufferProjection->Release();
				m_pConstantBufferProjection = nullptr;
			}
		}

		bool Init()
		{

			ID3D11Device& device = systems::DirectXGraphics::GetInstance()->GetDevice();

			// コンスタントバッファ作成
			bool sts = CreateConstantBuffer(
				&device,			// デバイス
				sizeof(ConstantBufferWorld),	// サイズ
				&m_pConstantBufferWorld);			// コンスタントバッファ２
			if (!sts)
			{
				MessageBox(NULL, TEXT("CreateBuffer(constant buffer world) error"), TEXT("Error"), MB_OK);
				return false;
			}

			// コンスタントバッファ作成
			sts = CreateConstantBuffer(
				&device,			// デバイス
				sizeof(ConstantBufferView),	// サイズ
				&m_pConstantBufferView);			// コンスタントバッファ２
			if (!sts) {
				MessageBox(NULL, TEXT("CreateBuffer(constant buffer view) error"), TEXT("Error"), MB_OK);
				return false;
			}

			// コンスタントバッファ作成
			sts = CreateConstantBuffer(
				&device,			// デバイス
				sizeof(ConstantBufferProjection),	// サイズ
				&m_pConstantBufferProjection);			// コンスタントバッファ２
			if (!sts) {
				MessageBox(NULL, TEXT("CreateBuffer(constant buffer projection) error"), TEXT("Error"), MB_OK);
				return false;
			}
			return true;
		}

		void SetTransform(TYPE type, DirectX::XMFLOAT4X4& matrix)
		{
			ALIGN16 XMMATRIX mat;
			mat = DirectX::XMLoadFloat4x4(&matrix);

			ID3D11DeviceContext& devicecontext = systems::DirectXGraphics::GetInstance()->GetImmediateContext();

			switch (type)
			{
			case TYPE::WORLD:
				m_CBWorld.World = XMMatrixTranspose(mat);
				devicecontext.UpdateSubresource(m_pConstantBufferWorld, 0, nullptr, &m_CBWorld, 0, 0);
				devicecontext.VSSetConstantBuffers(0, 1, &m_pConstantBufferWorld);
				devicecontext.PSSetConstantBuffers(0, 1, &m_pConstantBufferWorld);
				break;
			case TYPE::VIEW:
				m_CBView.View = XMMatrixTranspose(mat);
				devicecontext.UpdateSubresource(m_pConstantBufferView, 0, nullptr, &m_CBView, 0, 0);
				devicecontext.VSSetConstantBuffers(1, 1, &m_pConstantBufferView);
				devicecontext.PSSetConstantBuffers(1, 1, &m_pConstantBufferView);
				break;
			case TYPE::PROJECTION:
				m_CBProjection.Projection = XMMatrixTranspose(mat);
				devicecontext.UpdateSubresource(m_pConstantBufferProjection, 0, nullptr, &m_CBProjection, 0, 0);
				devicecontext.VSSetConstantBuffers(2, 1, &m_pConstantBufferProjection);
				devicecontext.PSSetConstantBuffers(2, 1, &m_pConstantBufferProjection);
				break;
			}
		}


	private:
		ID3D11Buffer* m_pConstantBufferWorld = nullptr;		// コンスタントバッファ2
		ID3D11Buffer* m_pConstantBufferView = nullptr;			// コンスタントバッファ2
		ID3D11Buffer* m_pConstantBufferProjection = nullptr;	// コンスタントバッファ2
		ConstantBufferWorld m_CBWorld;				// b0 
		ConstantBufferView m_CBView;				// b1
		ConstantBufferProjection m_CBProjection;	// b2
	};
}