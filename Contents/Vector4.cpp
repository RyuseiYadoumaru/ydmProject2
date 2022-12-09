//*****************************************************************************
//* @file   Vector4.h
//* @brief  4�����x�N�g���N���X
//* @note   4�����x�N�g���ƈʒu�\��
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include "Vector4.h"
#include "Vector3.h"

myMath::Vector4& myMath::Vector4::operator=(const Vector3& vec3) noexcept
{
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	w = 0.0f; 
	return *this;
}