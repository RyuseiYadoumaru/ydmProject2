//*****************************************************************************
//!	@file	Matrix4x4.h
//!	@brief	3D行列クラス　4*4
//!	@note	3D行列関連
//!	@author	YadoumaruRyusei
//*****************************************************************************


//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Matrix4x4.h"
#include "macro.h"


//==============================================================================
//!	@fn		CreateMatrixIdentity
//!	@brief	単位行列生成
//!	@retval	単位行列
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
//!	@brief	ワールド座標行列生成
//!	@param	Position
//!	@param	Rotation
//!	@param	Scale
//!	@retval	ワールド行列
//==============================================================================
myMath::Matrix4x4& myMath::Matrix4x4::CreateWorldMatrix(Vector3& position, Vector3& rotation, Vector3 scale) noexcept
{
	/****	行列変換	****/
	DirectX::XMMATRIX mtxPos = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	DirectX::XMMATRIX mtxRotX = DirectX::XMMatrixRotationX((DirectX::XMConvertToRadians(rotation.x)));
	DirectX::XMMATRIX mtxRotY = DirectX::XMMatrixRotationY((DirectX::XMConvertToRadians(rotation.y)));
	DirectX::XMMATRIX mtxRotZ = DirectX::XMMatrixRotationZ((DirectX::XMConvertToRadians(rotation.z)));

	DirectX::XMMATRIX mtxScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	/****	行列合成	****/
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

	/****	行列合成	****/
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

//整理
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
//!	@brief	クオータニオン生成
//!	@retval	クオータニオン
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
