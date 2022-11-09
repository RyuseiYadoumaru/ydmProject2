#include "VertexShader.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"
#include "../System/MessageWindow.h"

#include "ShaderManager.h"

USING_GAME_SYSTEMS;

bool GAME_SYSTEMS::VertexShader::LoadShader(T_String vsFilePath, D3D11_INPUT_ELEMENT_DESC* layout, uInt32 elementsNum)
{
	ID3D11Device& device = systems::DirectXGraphics::GetInstance()->GetDevice();

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	bool sts = CreateVertexShader(
		&device,
		vsFilePath.c_str(),
		"main",
		"vs_5_0",
		layout,
		elementsNum,
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

void GAME_SYSTEMS::VertexShader::BindShader()
{
    // �f�o�C�X�R���e�L�X�g
    ID3D11DeviceContext& devcontext = systems:: DirectXGraphics::GetInstance()->GetImmediateContext();
    // ���_�t�H�[�}�b�g���Z�b�g
    devcontext.IASetInputLayout(m_vertexLayout.Get());
    // ���_�V�F�[�_�[���Z�b�g
    devcontext.VSSetShader(m_vertexShader.Get(), nullptr, 0);

}
