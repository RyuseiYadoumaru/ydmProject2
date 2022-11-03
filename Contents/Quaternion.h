//*****************************************************************************
//* @file   Quaternion.h
//* @brief  クオータニオンクラス
//* @note   オブジェクトの回転指定を管理する
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
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
		static Quaternion CreateQuaternion(Matrix4x4& matrix);
		static Quaternion Multiply(const Quaternion& qt1, const Quaternion& qt2);
	public:
		void Set(Float32 _x, Float32 _y, Float32 _z, Float32 _w) noexcept { x = _x; y = _y; z = _z; w = _w; }
		void Set(DirectX::XMVECTOR& vector) noexcept { DirectX::XMStoreFloat4(this, vector); }

		void CreateRotationAxis(Vector4& axis, Float32 angle);

		DirectX::XMVECTOR GetXMVector() noexcept { return DirectX::XMVectorSet(x, y, z, w); }
		const Vector4& GetAxis() const noexcept { return m_axis; }

		void Normalize();

	public:
		Quaternion() = default;
		Quaternion(const Quaternion& qt) :
			DirectX::XMFLOAT4(qt.x, qt.y, qt.z, qt.w) { this->m_axis = qt.GetAxis(); }
		Quaternion(Float32 _x, Float32 _y, Float32 _z, Float32 _w) : DirectX::XMFLOAT4(_x, _y, _z, _w) {}

		Quaternion& operator=(const Quaternion&) = default;

	private:
		Vector4 m_axis;
	};
}