//*****************************************************************************
//* @file   DX11SetBoneMatrix.cpp
//* @brief  
//* @note   �{�[���ɕK�v�ȃf�[�^��萔�o�b�t�@�ɃZ�b�g����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "DX11SetBoneMatrix.h"
#include "MessageWindow.h"
#include "Skeleton.h"
#include "../dx11mathutil.h"


USING_SYSTEMS;


bool SYSTEMS::DX11SetBoneMatrix::Initialize()
{
    ID3D11Device& device = systems::DirectXGraphics::GetInstance()->GetDevice();
	bool sts = CreateConstantBufferWrite(
		&device,
		sizeof(ConstantBufferBoneMatrix),
		m_constantBufferBone.GetAddressOf());
	if (sts == false)
	{
		MessageWindow::Error(TEXT("ConstantBufferBoneMaterial�̐����Ɏ��s�I"));
		return false;
	}
    return true;
}

bool SYSTEMS::DX11SetBoneMatrix::Finalize()
{
	if (m_constantBufferBone != nullptr)
	{
		m_constantBufferBone = nullptr;
	}
    return true;
}

void SYSTEMS::DX11SetBoneMatrix::SetConstantBuffer(const Vector<DirectX::XMFLOAT4X4>& matrixList)
{
	// ������
	for (int i = 0; i < m_MaxBoneNum; i++)
	{
		DX11MtxIdentity(m_cbBone.BoneMatrix[i]);
	}

	// �{�[���Z�b�g
	int index = 0;
	for (auto& matrix : matrixList)
	{
		DX11MtxTranspose(m_cbBone.BoneMatrix[index], matrix);
		index++;
	}

	// �{�[���s��i�[�p�萔�o�b�t�@�X�V
	ID3D11DeviceContext& devicecontext = DirectXGraphics::GetInstance()->GetImmediateContext();
	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = devicecontext.Map(m_constantBufferBone.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) 
	{
		memcpy_s(pData.pData, pData.RowPitch, (void*)&m_cbBone, sizeof(ConstantBufferBoneMatrix));
		devicecontext.Unmap(m_constantBufferBone.Get(), 0);
	}
	devicecontext.VSSetConstantBuffers(5, 1, m_constantBufferBone.GetAddressOf());
}
