#include "Polygon.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;
USING_DIRECTX;

Polygon::Polygon(Vector<Vertex> vertices, Vector<unsigned int> indices)
{
	this->m_vertices = vertices;
	this->m_indices = indices;
	InitBuffers();
}

Polygon::Polygon(Vector<Vertex_Cube> vertices, Vector<unsigned int> indices)
{
	this->m_vx = vertices;
	this->m_indices = indices;
	InitBuffersCube();
}

void Polygon::Uninit()
{
	if (this->m_VertexBuffer == nullptr)
	{
		this->m_VertexBuffer->Release();
		this->m_VertexBuffer = nullptr;
	}

	if (this->m_IndexBuffer == nullptr)
	{
		this->m_IndexBuffer->Release();
		this->m_IndexBuffer = nullptr;
	}
}

void Polygon::Draw(ID3D11DeviceContext* devcon)
{
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;
	// ���_�o�b�t�@���Z�b�g
	devcon->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	devcon->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// �g�|���W�[���Z�b�g
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// �C���f�b�N�X�o�b�t�@�𗘗p���ĕ`��
	devcon->DrawIndexed(static_cast<unsigned int>(m_indices.size()), 0, 0);
}

bool Polygon::InitBuffers()
{
	ID3D11Device& dev = DirectXGraphics::GetInstance()->GetDevice();

	// ���_�o�b�t�@����
	bool sts = CreateVertexBufferWrite(
		&dev,
		static_cast<unsigned int>(sizeof(Vertex)),			// �X�g���C�h
		static_cast<unsigned int>(this->m_vertices.size()),		// ���_��
		this->m_vertices.data(),									// ���_�f�[�^
		&this->m_VertexBuffer);
	if (sts == false) 
	{
		return false;
	}

	// �C���f�b�N�X�o�b�t�@����
	sts = CreateIndexBuffer(
		&dev,
		static_cast<unsigned int>(this->m_indices.size()),
		this->m_indices.data(),
		&this->m_IndexBuffer);
	if (sts == false) 
	{
		return false;
	}
	return true;
}

bool GAME_SYSTEMS::Polygon::InitBuffersCube()
{
	ID3D11Device& dev = DirectXGraphics::GetInstance()->GetDevice();

	// ���_�o�b�t�@����
	bool sts = CreateVertexBufferWrite(
		&dev,
		static_cast<unsigned int>(sizeof(Vertex_Cube)),		// �X�g���C�h
		static_cast<unsigned int>(this->m_vx.size()),		// ���_��
		this->m_vx.data(),							// ���_�f�[�^
		&this->m_VertexBuffer);
	if (sts == false)
	{
		return false;
	}

	// �C���f�b�N�X�o�b�t�@����
	sts = CreateIndexBuffer(
		&dev,
		static_cast<unsigned int>(this->m_indices.size()),
		this->m_indices.data(),
		&this->m_IndexBuffer);
	if (sts == false)
	{
		return false;
	}
	return true;
}
