//*****************************************************************************
//* @file   Vector3.h
//* @brief  3Dベクトルクラス
//* @note   3Dベクトルと位置表現
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "std.h"
#include "macro.h"

namespace myMath
{
	class Matrix4x4;
	class Vector4;

	class Vector3 : public DirectX::XMFLOAT3
	{
	public:
		static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);
		static Vector3 Larp(const Vector3& startVec3, const Vector3& endVec3, Float32 t);
		static Vector3 Normalize(const Vector3& vec3);

	public:
		void Set(float _x, float _y, float _z) noexcept { x = _x; y = _y; z = _z; }
		void Set(DirectX::XMVECTOR& vector) noexcept { DirectX::XMStoreFloat3(this, vector); }

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
		Vector3 operator*(Float32 mul) const noexcept { return Vector3(x * mul, y * mul, z * mul); }
		Vector3& operator*=(const Vector3& vec3) noexcept { x *= vec3.x; y *= vec3.y; z *= vec3.z; return *this; }
		Vector3 operator/(const Vector3& vec3) const noexcept { return Vector3(x / vec3.x, y / vec3.y, z / vec3.z); }
		Vector3& operator/=(const Vector3& vec3) noexcept { x /= vec3.x; y /= vec3.y; z /= vec3.z; return *this; }
		bool operator!=(const Vector3& vec3)const noexcept { return (this->x != vec3.x && this->y != vec3.y && this->z != vec3.z); }
		bool operator==(const Vector3& vec3)const noexcept { return (this->x == vec3.x && this->y == vec3.y && this->z == vec3.z); }

		Vector3& operator=(const myMath::Vector4& vec4) noexcept;
	};
}