#include "Material.h"
#include "System/Shader.h"
#include "System/DirectxGraphics.h"

USING_SYSTEMS;
USING_DIRECTX;

Material::~Material()
{
	Unload();
}

bool Material::LoadShader(const T_Char* vsfile, const T_Char* psfile)
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

	ID3D11Device& device = DirectXGraphics::GetInstance()->GetDevice();

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	bool sts = CreateVertexShader(
		&device,
		vsfile,
		"main",
		"vs_5_0",
		layout,
		numElements,
		&this->m_pVertexShader,
		&this->m_pVertexLayout);
	if (!sts) {
		MessageBox(nullptr, TEXT("CreateVertexShader error"), TEXT("error"), MB_OK);
		return false;
	}

	// �s�N�Z���V�F�[�_�[�𐶐�
	sts = CreatePixelShader(			// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
		&device,		// �f�o�C�X�I�u�W�F�N�g
		psfile,
		"main",
		"ps_5_0",
		&this->m_pPixelShader);
	if (!sts) {
		MessageBox(nullptr, TEXT("CreatePixelShader error"), TEXT("error"), MB_OK);
		return false;
	}

	return true;
}

void Material::Unload()
{
	// ���_�V�F�[�_�[���
	if (m_pVertexShader) {
		this->m_pVertexShader->Release();
		this->m_pVertexShader = nullptr;
	}

	// �s�N�Z���V�F�[�_�[���
	if (m_pPixelShader) {
		this->m_pPixelShader->Release();
		this->m_pPixelShader = nullptr;
	}

	// ���_���C�A�E�g���
	if (m_pVertexLayout) {
		this->m_pVertexLayout->Release();
		this->m_pVertexLayout = nullptr;
	}
}

void Material::SetShader()
{
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext& devcontext = DirectXGraphics::GetInstance()->GetImmediateContext();
	// ���_�t�H�[�}�b�g���Z�b�g
	devcontext.IASetInputLayout(m_pVertexLayout);
	// ���_�V�F�[�_�[���Z�b�g
	devcontext.VSSetShader(m_pVertexShader, nullptr, 0);
	// �s�N�Z���V�F�[�_�[���Z�b�g
	devcontext.PSSetShader(m_pPixelShader, nullptr, 0);
}