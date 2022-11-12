//*****************************************************************************
//* @file   Cube.h
//* @brief  
//* @note   �L���[�u
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "macro.h"
#include "std.h"
#include "Color.h"

namespace GAME_SYSTEMS
{
	class Cube
	{
		struct  Vertex
		{
			DirectX::XMFLOAT3	Pos;
			DirectX::XMFLOAT4	Color;
			DirectX::XMFLOAT3	Normal;
		};

		struct  Face
		{
			uInt32 index[3];
		};

	public:
		bool Create();
		void Draw();

	private:
		void CreateIndex();
		void CreateVertex();

	private:
		Float32 m_size = 1.0f;
		MY_MATH::Color m_color = { 255.0f, 255.0f, 255.0f, 255.0f };

		Vector<Vertex> m_vertex;	//���_�f�[�^
		Vector<Face> m_face;

	private:
		ComPtr<ID3D11Buffer> m_vertexBuffer;		// ���_�o�b�t�@
		ComPtr<ID3D11Buffer> m_indexBuffer;		// �C���f�b�N�X�o�b�t�@
		ComPtr<ID3D11VertexShader> m_vertexShader;	// ���_�V�F�[�_�[
		ComPtr<ID3D11PixelShader> m_pixelShader;	// �s�N�Z���V�F�[�_�[
		ComPtr<ID3D11InputLayout>  m_vertexLayout;	// ���_���C�A�E�g

	};
}
