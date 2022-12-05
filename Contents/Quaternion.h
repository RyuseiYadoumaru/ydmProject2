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

		static Quaternion Multiply(const Quaternion& qt1, const Quaternion& qt2);
		static Quaternion Slerp(const Quaternion& startQt, const Quaternion& endQt, Float32 t);
	public:
		void Set(Float32 _x, Float32 _y, Float32 _z, Float32 _w) noexcept { x = _x; y = _y; z = _z; w = _w; }
		void Set(DirectX::XMVECTOR& vector) noexcept 
		{
			Quaternion set(0.0f, 0.0f, 0.0f, 0.0f);
			DirectX::XMStoreFloat4(&set, vector);
			this->x = set.x;
			this->y = set.y;
			this->z = set.z;
			this->w = set.w;
		}

		void CreateRotationAxis(Vector4& axis, Float32 angle);

		DirectX::XMVECTOR GetXMVector() noexcept { return DirectX::XMVectorSet(x, y, z, w); }
		const Vector4& GetAxis() const noexcept { return m_axis; }

		void Normalize();

	public:
		Quaternion() : DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f) {}
		Quaternion(const Quaternion& qt) = default;
		Quaternion(Float32 _x, Float32 _y, Float32 _z, Float32 _w) : DirectX::XMFLOAT4(_x, _y, _z, _w) {}

		Quaternion& operator=(const Quaternion&) = default;

	private:
		Vector4 m_axis;

	};
}