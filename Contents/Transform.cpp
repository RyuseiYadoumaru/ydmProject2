//*****************************************************************************
//* @file   Transform.h
//* @brief  トランスフォームクラス
//* @note   全てのオブジェクトの座標系を管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Transform.h"

USING_GAME_SYSTEMS;

//整理
void Transform::Add(Transform::Field type, Float32 x, Float32 y, Float32 z)
{
	switch (type)
	{
	case Transform::Field::Position:
	{
		Float32 posValX = m_position.x + x;
		Float32 posValY = m_position.y + y;
		Float32 posValZ = m_position.z + z;
		Set(Transform::Field::Position, posValX, posValY, posValZ);
	}break;

	case Transform::Field::Rotation:
	{
		Float32 rotValX = m_rotation.x + x;
		Float32 rotValY = m_rotation.y + y;
		Float32 rotValZ = m_rotation.z + z;
		Set(Transform::Field::Rotation, rotValX, rotValY, rotValZ);
	}break;

	case Transform::Field::Scale:
	{
		Float32 scaValX = m_scale.x + x;
		Float32 scaValY = m_scale.y + y;
		Float32 scaValZ = m_scale.z + z;
		Set(Transform::Field::Scale, scaValX, scaValY, scaValZ);
	}break;
	}
}

void Transform::Set(Transform::Field type, Float32 x, Float32 y, Float32 z)
{
	switch (type)
	{
	case Transform::Field::Position:
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;

	}break;

	case Transform::Field::Rotation:
	{
		//m_rotation.Set(0.0f, 0.0f, 0.0f);
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;

#if 1
		/****	各軸クォータニオン生成	****/
		myMath::Quaternion qtX;
		qtX.CreateRotationAxis(GetAxisX(), m_rotation.x);
		myMath::Quaternion qtY;
		qtY.CreateRotationAxis(GetAxisY(), m_rotation.y);
		myMath::Quaternion qtZ;
		qtZ.CreateRotationAxis(GetAxisZ(), m_rotation.z);

		/****	クォータニオン合成	****/
		myMath::Quaternion temp1 = myMath::Quaternion::Multiply(qtX, qtY);
		m_quaternion = myMath::Quaternion::Multiply(temp1, qtZ);
		//myMath::Quaternion qtMatrix = myMath::Quaternion::CreateQuaternion(m_worldMatrix);
		//myMath::Quaternion temp1 = myMath::Quaternion::Multiply(qtMatrix, qtX);
		//myMath::Quaternion temp2 = myMath::Quaternion::Multiply(qtY, qtZ);
		//m_quaternion = myMath::Quaternion::Multiply(temp2, temp1);

		m_quaternion.Normalize();
#else
		/****	回転行列生成	****/
		myMath::Matrix4x4 rotX = myMath::Matrix4x4::CreateRotationXMatrix(m_rotation.x);
		myMath::Matrix4x4 rotY = myMath::Matrix4x4::CreateRotationYMatrix(m_rotation.y);
		myMath::Matrix4x4 rotZ = myMath::Matrix4x4::CreateRotationZMatrix(m_rotation.z);

		/****	クォータニオン変換	****/
		myMath::Quaternion qtX = myMath::Quaternion::CreateQuaternion(rotX);
		myMath::Quaternion qtY = myMath::Quaternion::CreateQuaternion(rotY);
		myMath::Quaternion qtZ = myMath::Quaternion::CreateQuaternion(rotZ);
		myMath::Quaternion mtxQt = myMath::Quaternion::CreateQuaternion(m_worldMatrix);

		/****	合成	****/
		myMath::Quaternion temp1 = myMath::Quaternion::Multiply(mtxQt, qtX);
		myMath::Quaternion temp2 = myMath::Quaternion::Multiply(qtY, qtZ);
		m_quaternion = myMath::Quaternion::Multiply(temp2, temp1);
		m_quaternion.Normalize();

#endif // 0

	}break;

	case Transform::Field::Scale:
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;

	}break;
	}

	/****	行列生成	****/
	SetWorldMatrix();
}

//==============================================================================
//!	@fn		GetAxisX
//!	@brief	X軸取得
//==============================================================================
myMath::Vector4& Transform::GetAxisX()
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
//!	@brief	Y軸取得
//==============================================================================
myMath::Vector4& Transform::GetAxisY()
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
//!	@brief	Z軸取得
//==============================================================================
myMath::Vector4& Transform::GetAxisZ()
{
	myMath::Vector4 axisZ;
	axisZ.x = m_worldMatrix._31;
	axisZ.y = m_worldMatrix._32;
	axisZ.z = m_worldMatrix._33;
	axisZ.w = 0.0f;

	return axisZ;
}



void Transform::SetWorldMatrix()
{
	/****	回転行列生成	****/
	myMath::Matrix4x4 rotMatrix = myMath::Matrix4x4::CreateMatrixQuaternion(m_quaternion);

	/****	行列セット	****/
	m_worldMatrix._11 = m_scale.x * rotMatrix._11;
	m_worldMatrix._12 = m_scale.x * rotMatrix._12;
	m_worldMatrix._13 = m_scale.x * rotMatrix._13;
	m_worldMatrix._14 = 0.0f;

	m_worldMatrix._21 = m_scale.y * rotMatrix._21;
	m_worldMatrix._22 = m_scale.y * rotMatrix._22;
	m_worldMatrix._23 = m_scale.y * rotMatrix._23;
	m_worldMatrix._24 = 0.0f;

	m_worldMatrix._31 = m_scale.z * rotMatrix._31;
	m_worldMatrix._32 = m_scale.z * rotMatrix._32;
	m_worldMatrix._33 = m_scale.z * rotMatrix._33;
	m_worldMatrix._34 = 0.0f;

	m_worldMatrix._41 = m_position.x;
	m_worldMatrix._42 = m_position.y;
	m_worldMatrix._43 = m_position.z;
	m_worldMatrix._44 = 1.0f;


}

void GAME_SYSTEMS::Transform::Start()
{
	m_position.Set(0.0f, 0.0f, 0.0f);
	m_rotation.Set(0.0f, 0.0f, 0.0f);
	m_scale.Set(1.0f, 1.0f, 1.0f);

	SetWorldMatrix();
}

void Transform::Update()
{
}

void GAME_SYSTEMS::Transform::End()
{
}