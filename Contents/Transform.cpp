//*****************************************************************************
//* @file   Transform.h
//* @brief  �g�����X�t�H�[���N���X
//* @note   �S�ẴI�u�W�F�N�g�̍��W�n���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Transform.h"

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
	//m_position.Set(0.0f, 0.0f, 0.0f);
	//m_rotation.Set(90.0f, 0.0f, 0.0f);
	//m_scale.Set(1.0f, 1.0f, 1.0f);

}

void Transform::Update()
{
	Matrix4x4 matrix = Matrix4x4::CreateWorldMatrix(m_position, m_rotation, m_scale);
	m_worldMatrix = matrix;
}

void GAME_SYSTEMS::Transform::End()
{
}