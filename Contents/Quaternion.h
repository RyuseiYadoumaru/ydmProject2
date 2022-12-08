//*****************************************************************************
//* @file   Quaternion.h
//* @brief  クオータニオンクラス
//* @note   オブジェクトの回転指定を管理する
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "std.h"
#include "Vector4.h"
#include "Vector3.h"

namespace myMath
{
	class Matrix4x4;
}

namespace myMath
{
	class Quaternion : public DirectX::XMFLOAT4
	{
	public:
		static Quaternion CreateByMartix(Matrix4x4& matrix);
		static Quaternion CreateByRotation(Float32 x, Float32 y, Float32 z);
		static Quaternion CreateByRotationAxis(const Vector4& axis, Float32 angle);

		static Vector3 EulerAngles(const Quaternion& qt);

		static Quaternion Multiply(const Quaternion& qt1, const Quaternion& qt2);
		static Quaternion Slerp(const Quaternion& startQt, const Quaternion& endQt, Float32 t);
		static Quaternion Normalize(Quaternion& qt);
	public:
		void Set(Float32 _x, Float32 _y, Float32 _z, Float32 _w) noexcept { x = _x; y = _y; z = _z; w = _w; }
		void Set(DirectX::XMVECTOR& vector) noexcept 
		{
			Quaternion set(0.0f, 0.0f, 0.0f, 1.0f);
			DirectX::XMStoreFloat4(&set, vector);
			this->x = set.x;
			this->y = set.y;
			this->z = set.z;
			this->w = set.w;
		}


		DirectX::XMVECTOR GetXMVector() noexcept { return DirectX::XMVectorSet(x, y, z, w); }
		myMath::Vector3 GetVector3() const noexcept { return myMath::Vector3(x, y, z); }
		myMath::Vector4 GetVector4() const noexcept { return myMath::Vector4(x, y, z, w); }
		void Normalize();

	public:
		explicit Quaternion() : DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) {}
		explicit Quaternion(Float32 _x, Float32 _y, Float32 _z, Float32 _w) : DirectX::XMFLOAT4(_x, _y, _z, _w) {}
		Quaternion(const Quaternion& qt) = default;
		Quaternion& operator=(const Quaternion&) = default;
		Quaternion operator*(const Quaternion& qt) { return Quaternion::Multiply(*this, qt); }
		Quaternion& operator=(const Vector3& vec3) { x = vec3.x; y = vec3.y; z = vec3.z; w = 0.0f; return *this; }
		Quaternion& operator=(const Vector4& vec4) { x = vec4.x; y = vec4.y; z = vec4.z; w = vec4.w; return *this; }
	};
}