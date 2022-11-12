#pragma once
#include "macro.h"
#include "std.h"
#include <DirectXMath.h>
#include <d3d11.h>

struct Vertex
{
	DirectX::XMFLOAT3 m_Pos;	// �ʒu
	DirectX::XMFLOAT3 m_Normal;	// �@��
	DirectX::XMFLOAT2 m_Tex;	// UV���W
	int32_t	m_BoneIndex[4];	//�{�[���C���f�b�N�X
	float	m_BoneWeight[4];// �E�F�C�g�l
	int32_t	m_BoneNum;		// �{�[����
};

struct Vertex_Cube
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
	DirectX::XMFLOAT3 Normal;
};


namespace GAME_SYSTEMS
{
	class Polygon
	{
	public:
		Polygon(Vector<Vertex> vertices, Vector<unsigned int> indices);
		Polygon(Vector<Vertex_Cube>vertices, Vector<uInt32> indices);
	
	public:
		void Uninit(); // �㏈��
		void Draw(ID3D11DeviceContext* devcon);
	
	private:
		bool InitBuffers(); // �o�b�t�@������
		bool InitBuffersCube(); // �o�b�t�@������
	
	private:
		Vector<Vertex> m_vertices;			// ���_�f�[�^
		Vector<Vertex_Cube> m_vx;			// ���_�f�[�^
		
		Vector<unsigned int> m_indices;
	
	private:
		ID3D11Buffer* m_VertexBuffer;			// ���_�o�b�t�@
		ID3D11Buffer* m_IndexBuffer;
	};
}