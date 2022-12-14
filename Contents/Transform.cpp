//*****************************************************************************
//* @file   Transform.h
//* @brief  トランスフォームクラス
//* @note   全てのオブジェクトの座標系を管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Transform.h"
#include "myMath.h"

USING_GAME_SYSTEMS;
USING_MY_MATH;

myMath::Matrix4x4 GAME_SYSTEMS::Transform::CreateViewMatrix(const Transform& transform)
{
	myMath::Matrix4x4 worldMatrix = transform.m_worldMatrix;
	DirectX::XMMATRIX viewMtx = DirectX::XMMatrixInverse(nullptr, worldMatrix.GetXMMatrix());
	myMath::Matrix4x4 viewMatrix;
	viewMatrix.Set(viewMtx);
	return viewMatrix;
}

Vector3 GAME_SYSTEMS::Transform::RotationMatrixToEuler(const Matrix4x4& rotMtx)
{
	Vector3 radian;
	auto mtx = Matrix4x4::CreateTransposeMatrix(rotMtx);
	radian.x = atan2(mtx._32, mtx._33);
	radian.y = asin(mtx._31 * -1.0f);
	radian.z = atan2(mtx._21, mtx._11);

	Vector3 degree;
	degree.x = Math::RadiansToDegrees(radian.x);
	degree.y = Math::RadiansToDegrees(radian.y);
	degree.z = Math::RadiansToDegrees(radian.z);
	return degree;
}

void GAME_SYSTEMS::Transform::SetRotation(Float32 x, Float32 y, Float32 z) noexcept
{
	m_Rotation = myMath::Quaternion::CreateByRotation(x, y, z);
}

Vector3 GAME_SYSTEMS::Transform::GetEulerAngles() noexcept
{
	Matrix4x4 mtx = Matrix4x4::CreateMatrixFromQuaternion(m_Rotation);
	Vector3 outRot = Transform::RotationMatrixToEuler(mtx);
	return outRot;
}

myMath::Vector4 Transform::GetAxisX()
{
	myMath::Vector4 axisX;
	axisX.x = m_worldMatrix._11;
	axisX.y = m_worldMatrix._12;
	axisX.z = m_worldMatrix._13;
	axisX.w = 0.0f;

	return axisX;
}

myMath::Vector4 Transform::GetAxisY()
{
	myMath::Vector4 axisY;
	axisY.x = m_worldMatrix._21;
	axisY.y = m_worldMatrix._22;
	axisY.z = m_worldMatrix._23;
	axisY.w = 0.0f;

	return axisY;
}

myMath::Vector4 Transform::GetAxisZ()
{
	myMath::Vector4 axisZ;
	axisZ.x = m_worldMatrix._31;
	axisZ.y = m_worldMatrix._32;
	axisZ.z = m_worldMatrix._33;
	axisZ.w = 0.0f;

	return axisZ;
}

void GAME_SYSTEMS::Transform::Start()
{
}

void Transform::Update()
{	
	// 行列生成
	m_Rotation.Normalize();
	Matrix4x4 posMat = Matrix4x4::CreateTranslationMatrix(m_Position);
	Matrix4x4 rotMat = Matrix4x4::CreateMatrixFromQuaternion(m_Rotation);
	Matrix4x4 scaleMat = Matrix4x4::CreateScaleMatrix(m_Scale);
	Matrix4x4 mtx = Matrix4x4::CreateWorldMatrix(posMat, rotMat, scaleMat);
	m_worldMatrix = mtx;
	m_Rotation = Quaternion::CreateByMartix(m_worldMatrix);
}

void GAME_SYSTEMS::Transform::End()
{
}