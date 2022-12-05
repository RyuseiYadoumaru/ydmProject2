//*****************************************************************************
//* @file   Transform.h
//* @brief  �g�����X�t�H�[���N���X
//* @note   �S�ẴI�u�W�F�N�g�̍��W�n���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Transform.h"
#include "myMath.h"

USING_GAME_SYSTEMS;
USING_MY_MATH;

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
	m_rotation = myMath::Quaternion::CreateByRotation(x, y, z);
}

Vector3 GAME_SYSTEMS::Transform::GetEulerAngles() noexcept
{
	Matrix4x4 mtx = Matrix4x4::CreateMatrixFromQuaternion(m_rotation);
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
	// �s�񐶐�
	Matrix4x4 matrix = Matrix4x4::CreateMatrixFromQuaternion(m_rotation);
	matrix._11 *= m_scale.x;
	matrix._12 *= m_scale.x;
	matrix._13 *= m_scale.x;
	matrix._14 = 0.0f;

	matrix._21 *= m_scale.y;
	matrix._22 *= m_scale.y;
	matrix._23 *= m_scale.y;
	matrix._24 = 0.0f;

	matrix._31 *= m_scale.z;
	matrix._32 *= m_scale.z;
	matrix._33 *= m_scale.z;
	matrix._34 = 0.0f;

	matrix._41 = m_position.x;
	matrix._42 = m_position.y;
	matrix._43 = m_position.z;
	matrix._44 = 1.0f;

	m_worldMatrix = matrix;
}

void GAME_SYSTEMS::Transform::End()
{
}