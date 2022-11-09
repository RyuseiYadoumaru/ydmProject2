#include "VertexShader.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"
#include "../System/MessageWindow.h"


bool GAME_SYSTEMS::VertexShader::LoadShader(T_String vsFilePath)
{
	// ���_�f�[�^�̒�`�i�A�j���[�V�����Ή��j
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEINDEX",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	ID3D11Device& device = systems::DirectXGraphics::GetInstance()->GetDevice();

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	bool sts = CreateVertexShader(
		&device,
		vsFilePath.c_str(),
		"main",
		"vs_5_0",
		layout,
		numElements,
		&this->m_vertexShader,
		&this->m_vertexLayout);
	if (sts == false) 
	{
		systems::MessageWindow::GetInstance()->Error(TEXT("CreateVertexShader error"));
		return false;
	}
	return true;
}

void GAME_SYSTEMS::VertexShader::Releace()
{
    if (m_vertexShader != nullptr)
    {
        m_vertexShader->Release();
        m_vertexShader = nullptr;
    }
    if (m_vertexLayout != nullptr)
    {
        m_vertexLayout->Release();
        m_vertexLayout = nullptr;
    }
}

void GAME_SYSTEMS::VertexShader::SetShader()
{
    // �f�o�C�X�R���e�L�X�g
    ID3D11DeviceContext& devcontext = systems:: DirectXGraphics::GetInstance()->GetImmediateContext();
    // ���_�t�H�[�}�b�g���Z�b�g
    devcontext.IASetInputLayout(m_vertexLayout.Get());
    // ���_�V�F�[�_�[���Z�b�g
    devcontext.VSSetShader(m_vertexShader.Get(), nullptr, 0);

}
