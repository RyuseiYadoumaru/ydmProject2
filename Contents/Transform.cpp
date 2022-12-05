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

//==============================================================================
//!	@fn		GetAxisX
//!	@brief	X���擾
//==============================================================================
myMath::Vector4 Transform::GetAxisX()
{
	myMath::Vector4 axisX;
	axisX.x = m_worldMatrix._11;
	axisX.y = m_worldMatrix._12;
	axisX.z = m_worldMatrix._13;
	axisX.w = 0.0f;

	return axisX;
}


//==============================================================================
//!	@fn		GetAxisY
//!	@brief	Y���擾
//==============================================================================
myMath::Vector4 Transform::GetAxisY()
{
	myMath::Vector4 axisY;
	axisY.x = m_worldMatrix._21;
	axisY.y = m_worldMatrix._22;
	axisY.z = m_worldMatrix._23;
	axisY.w = 0.0f;

	return axisY;
}


//==============================================================================
//!	@fn		GetAxisZ
//!	@brief	Z���擾
//==============================================================================
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
	// �N�H�[�^�j�I������
	Float32 roll = MY_MATH::Math::DegreesToRadians(m_rotation.x);
	Float32 pich = MY_MATH::Math::DegreesToRadians(m_rotation.y);
	Float32 yow = MY_MATH::Math::DegreesToRadians(m_rotation.z);
	m_quaternion = Quaternion::CreateByRotation(roll, pich, yow);
	
	// �s�񐶐�
	Matrix4x4 matrix = Matrix4x4::CreateMatrixFromQuaternion(m_quaternion);
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