//*****************************************************************************
//* @file   Vector3.h
//* @brief  3D�x�N�g���N���X
//* @note   3D�x�N�g���ƈʒu�\��
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "std.h"

namespace myMath
{
	class Vector3 : public DirectX::XMFLOAT3
	{
	public:
		void Set(float _x, float _y, float _z) noexcept { x = _x; y = _y; z = _z; }
		DirectX::XMVECTOR GetXMVector() noexcept { return DirectX::XMVectorSet(x, y, z, 0.0f); }


	public:
		Vector3() : DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f) {}
		Vector3(float _x, float _y, float _z) : DirectX::XMFLOAT3(_x, _y, _z) {}

		Vector3& operator=(const Vector3& vec3) noexcept { x = vec3.x; y = vec3.y; z = vec3.z; return *this; }
		Vector3& operator=(const DirectX::XMFLOAT3& vec3) noexcept { x = vec3.x; y = vec3.y; z = vec3.z; return *this; }
		Vector3 operator+(const Vector3& vec3) const noexcept { return Vector3(x + vec3.x, y + vec3.y, z + vec3.z); }
		Vector3& operator+=(const Vector3& vec3)  noexcept { x += vec3.x; y += vec3.y; z += vec3.z; return *this; }
		Vector3 operator-(const Vector3& vec3) const noexcept { return Vector3(x - vec3.x, y - vec3.y, z - vec3.z); }
		Vector3& operator-=(const Vector3& vec3) noexcept { x -= vec3.x; y -= vec3.y; z -= vec3.z; return *this; }
		Vector3 operator*(const Vector3& vec3) const noexcept { return Vector3(x * vec3.x, y * vec3.y, z * vec3.z); }
		Vector3& operator*=(const Vector3& vec3) noexcept { x *= vec3.x; y *= vec3.y; z *= vec3.z; return *this; }
		Vector3 operator/(const Vector3& vec3) const noexcept { return Vector3(x / vec3.x, y / vec3.y, z / vec3.z); }
		Vector3& operator/=(const Vector3& vec3) noexcept { x /= vec3.x; y /= vec3.y; z /= vec3.z; return *this; }
		bool operator!=(const Vector3& vec3)const noexcept { return (this->x != vec3.x && this->y != vec3.y && this->z != vec3.z); }
		bool operator==(const Vector3& vec3)const noexcept { return (this->x == vec3.x && this->y == vec3.y && this->z == vec3.z); }
	};
}