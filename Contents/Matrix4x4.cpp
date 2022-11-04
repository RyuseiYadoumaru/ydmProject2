//*****************************************************************************
//!	@file	Matrix4x4.h
//!	@brief	3D�s��N���X�@4*4
//!	@note	3D�s��֘A
//!	@author	YadoumaruRyusei
//*****************************************************************************


//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Matrix4x4.h"
#include "macro.h"


//==============================================================================
//!	@fn		CreateMatrixIdentity
//!	@brief	�P�ʍs�񐶐�
//!	@retval	�P�ʍs��
//==============================================================================
myMath::Matrix4x4& myMath::Matrix4x4::CreateMatrixIdentity() noexcept
{
	ALIGN16 DirectX::XMMATRIX matrix;
	matrix = DirectX::XMMatrixIdentity();

	Matrix4x4 out;
	out.Set(matrix);

	return out;
}

//==============================================================================
//!	@fn		CreateWorldMatrix
//!	@brief	���[���h���W�s�񐶐�
//!	@param	Position
//!	@param	Rotation
//!	@param	Scale
//!	@retval	���[���h�s��
//==============================================================================
myMath::Matrix4x4& myMath::Matrix4x4::CreateWorldMatrix(Vector3& position, Vector3& rotation, Vector3 scale) noexcept
{
	/****	�s��ϊ�	****/
	DirectX::XMMATRIX mtxPos = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	DirectX::XMMATRIX mtxRotX = DirectX::XMMatrixRotationX((DirectX::XMConvertToRadians(rotation.x)));
	DirectX::XMMATRIX mtxRotY = DirectX::XMMatrixRotationY((DirectX::XMConvertToRadians(rotation.y)));
	DirectX::XMMATRIX mtxRotZ = DirectX::XMMatrixRotationZ((DirectX::XMConvertToRadians(rotation.z)));

	DirectX::XMMATRIX mtxScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	/****	�s�񍇐�	****/
	DirectX::XMMATRIX mtx = mtxScale * mtxRotX * mtxRotY * mtxRotZ * mtxPos;

	Matrix4x4 worldMatrix;
	worldMatrix.Set(mtx);

	return worldMatrix;
}

myMath::Matrix4x4& myMath::Matrix4x4::CreateWorldMatrix(Matrix4x4& position, Matrix4x4& rotation, Matrix4x4& scale) noexcept
{
	ALIGN16 DirectX::XMMATRIX mtxPos = position.GetXMMatrix();
	ALIGN16 DirectX::XMMATRIX mtxRot = rotation.GetXMMatrix();
	ALIGN16 DirectX::XMMATRIX mtxSca = scale.GetXMMatrix();

	/****	�s�񍇐�	****/
	ALIGN16 DirectX::XMMATRIX mtx = mtxSca * mtxRot * mtxPos;

	Matrix4x4 worldMatrix;
	worldMatrix.Set(mtx);

	return worldMatrix;
}

myMath::Matrix4x4 myMath::Matrix4x4::CreateMatrixQuaternion(Quaternion& quaternion) noexcept
{
	ALIGN16 DirectX::XMMATRIX mtx;
	ALIGN16 DirectX::XMVECTOR qtVec;
	qtVec = quaternion.GetXMVector();
	mtx = DirectX::XMMatrixRotationQuaternion(qtVec);

	Matrix4x4 out;
	out.Set(mtx);
	return out;
}

//����
myMath::Matrix4x4 myMath::Matrix4x4::CreateRotationXMatrix(Float32 rotationX)
{
	Float32 radians = (DirectX::XMConvertToRadians(rotationX));
	DirectX::XMMATRIX mtxRotX = DirectX::XMMatrixRotationX(radians);

	Matrix4x4 out;
	out.Set(mtxRotX);
	return out;
}

myMath::Matrix4x4 myMath::Matrix4x4::CreateRotationYMatrix(Float32 rotationY)
{
	Float32 radians = (DirectX::XMConvertToRadians(rotationY));
	DirectX::XMMATRIX mtxRotY = DirectX::XMMatrixRotationY(radians);

	Matrix4x4 out;
	out.Set(mtxRotY);
	return out;
}

myMath::Matrix4x4 myMath::Matrix4x4::CreateRotationZMatrix(Float32 rotationZ)
{
	Float32 radians = (DirectX::XMConvertToRadians(rotationZ));
	DirectX::XMMATRIX mtxRotZ = DirectX::XMMatrixRotationZ(radians);

	Matrix4x4 out;
	out.Set(mtxRotZ);
	return out;
}


//==============================================================================
//!	@fn		CreateQuaternion
//!	@brief	�N�I�[�^�j�I������
//!	@retval	�N�I�[�^�j�I��
//==============================================================================
myMath::Vector4& myMath::Matrix4x4::GetQuaternion() noexcept
{
	ALIGN16 DirectX::XMMATRIX mtx;
	ALIGN16 DirectX::XMVECTOR qt;
	mtx = this->GetXMMatrix();
	qt = DirectX::XMQuaternionRotationMatrix(mtx);

	myMath::Vector4 outQt;
	outQt.Set(qt);

	return outQt;
}
