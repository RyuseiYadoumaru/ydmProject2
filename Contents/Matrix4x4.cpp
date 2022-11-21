//*****************************************************************************
//!	@file	Matrix4x4.h
//!	@brief	3D行列クラス　4*4
//!	@note	3D行列関連
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "Matrix4x4.h"
#include "macro.h"


myMath::Matrix4x4 myMath::Matrix4x4::MatrixMultiply(Matrix4x4& mtx1, Matrix4x4& mtx2) noexcept
{
	Matrix4x4 outMtx;
	ALIGN16 DirectX::XMMATRIX mat1, mat2, matAns;

	mat1 = mtx1.GetXMMatrix();
	mat2 = mtx2.GetXMMatrix();

	matAns = XMMatrixMultiply(mat1, mat2);

	DirectX::XMFLOAT4X4 ans;
	XMStoreFloat4x4(&ans, matAns);
	outMtx.Set(ans);
	return outMtx;
}

//==============================================================================
//!	@fn		CreateMatrixIdentity
//!	@brief	単位行列生成
//!	@retval	単位行列
//==============================================================================
myMath::Matrix4x4 myMath::Matrix4x4::CreateMatrixIdentity() noexcept
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
myMath::Matrix4x4 myMath::Matrix4x4::CreateWorldMatrix(Vector3& position, Vector3& rotation, Vector3 scale) noexcept
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

myMath::Matrix4x4 myMath::Matrix4x4::CreateWorldMatrix(Matrix4x4& position, Matrix4x4& rotation, Matrix4x4& scale) noexcept
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

myMath::Matrix4x4 myMath::Matrix4x4::CreateLookAtMatrix(Vector3& eye, Vector3& lookat, Vector3& up, HandType type)
{
	ALIGN16 DirectX::XMVECTOR eyeVac	= eye.GetXMVector();
	ALIGN16 DirectX::XMVECTOR lookatVec = lookat.GetXMVector();
	ALIGN16 DirectX::XMVECTOR upVec		= up.GetXMVector();

	// 行列生成
	ALIGN16 DirectX::XMMATRIX lookAtMatrix;
	lookAtMatrix = DirectX::XMMatrixLookAtLH(eyeVac, lookatVec, upVec);

	Matrix4x4 cameraMatrix;
	cameraMatrix.Set(lookAtMatrix);
	return cameraMatrix;
}

myMath::Matrix4x4 myMath::Matrix4x4::CreateProjectionMatrix(Float32 fov, Float32 aspect, Float32 nearClip, Float32 farClip, HandType type)
{
	ALIGN16 DirectX::XMMATRIX mtx;
	mtx = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearClip, farClip);
	Matrix4x4 projection;
	projection.Set(mtx);
	return projection;
}

myMath::Matrix4x4 myMath::Matrix4x4::CreateTranslationMatrix(const Vector3& vector3)
{
	Matrix4x4 outMtx;

	ALIGN16 DirectX::XMMATRIX matTrans;
	matTrans = DirectX::XMMatrixTranslation(vector3.x, vector3.y, vector3.z);
	outMtx.Set(matTrans);

	return outMtx;
}

myMath::Matrix4x4 myMath::Matrix4x4::CreateMatrixFromQuaternion(Quaternion quaternion) noexcept
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

myMath::Matrix4x4 myMath::Matrix4x4::CreateMatrixFromAIMatrix(aiMatrix4x4& aiMtx)
{
	Matrix4x4 mtx;
	mtx._11 = aiMtx.a1;
	mtx._21 = aiMtx.a2;
	mtx._31 = aiMtx.a3;
	mtx._41 = aiMtx.a4;

	mtx._12 = aiMtx.b1;
	mtx._22 = aiMtx.b2;
	mtx._32 = aiMtx.b3;
	mtx._42 = aiMtx.b4;

	mtx._13 = aiMtx.c1;
	mtx._23 = aiMtx.c2;
	mtx._33 = aiMtx.c3;
	mtx._43 = aiMtx.c4;

	mtx._14 = aiMtx.d1;
	mtx._24 = aiMtx.d2;
	mtx._34 = aiMtx.d3;
	mtx._44 = aiMtx.d4;

	return mtx;;
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
