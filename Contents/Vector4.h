//*****************************************************************************
//* @file   Vector4.h
//* @brief  4次元ベクトルクラス
//* @note   4次元ベクトルと位置表現
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include <DirectXMath.h>
#include "std.h"
#include "Color.h"

namespace myMath
{
	class Vector4 : public DirectX::XMFLOAT4
	{
	public:
		/**
		 *  Vector4の内積計算.
		 * 
		 * !@param vec1 : vector4
		 * !@param vec2 : vector4
		 * !@return cosΘのRadian
		 */
		static Float32 Dot(Vector4& vec1, Vector4& vec2)
		{
			DirectX::XMVECTOR dot = DirectX::XMVector4Dot(vec1.GetXMVector(), vec2.GetXMVector());
			Vector4 dotVec;
			DirectX::XMStoreFloat4(&dotVec ,dot);
			return dotVec.x;
		}

	public:
		// パラメータセット
		void Set(Float32 _x, Float32 _y, Float32 _z, Float32 _w) noexcept { x = _x; y = _y; z = _z; w = _w; }
		void Set(DirectX::XMVECTOR& vector) noexcept { DirectX::XMStoreFloat4(this, vector); }
		
		// DirectXベクトルを取得
		DirectX::XMVECTOR GetXMVector() noexcept { return DirectX::XMVectorSet(x, y, z, w); }
		
		// 反対ベクトル取得
		Vector4 Reverse() noexcept { return Vector4(x * -1.0f, y * -1.0f, z * -1.0f, w); }

	public:
		Vector4() : DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f) {}
		Vector4(float _x, float _y, float _z, float _w) : DirectX::XMFLOAT4(_x, _y, _z, _w) {}

		Vector4& operator=(const Vector4& vec4) noexcept { x = vec4.x; y = vec4.y; z = vec4.z; w = vec4.w; return *this; }
		Vector4& operator=(const DirectX::XMFLOAT4& vec4) noexcept { x = vec4.x; y = vec4.y; z = vec4.z; w = vec4.w; return *this; }
		Vector4& operator=(const Color& vec4) noexcept { x = vec4.r; y = vec4.g; z = vec4.b; w = vec4.a; return *this; }
		Vector4 operator+(const Vector4& vec4) const noexcept { return Vector4(x + vec4.x, y + vec4.y, z + vec4.z, w + vec4.w); }
		Vector4& operator+=(const Vector4& vec4)  noexcept { x += vec4.x; y += vec4.y; z += vec4.z; w += vec4.w; return *this; }
		Vector4 operator-(const Vector4& vec4) const noexcept { return Vector4(x - vec4.x, y - vec4.y, z - vec4.z, w - vec4.w); }
		Vector4& operator-=(const Vector4& vec4) noexcept { x -= vec4.x; y -= vec4.y; z -= vec4.z; w -= vec4.w; return*this; }
		Vector4 operator*(const Vector4& vec4) const noexcept { return Vector4(x * vec4.x, y * vec4.y, z * vec4.z, w * vec4.w); }
		Vector4& operator*=(const Vector4& vec4) noexcept { x *= vec4.x; y *= vec4.y; z *= vec4.z; w *= vec4.w; return *this; }
		Vector4 operator/(const Vector4& vec4) const noexcept { return Vector4(x / vec4.x, y / vec4.y, z / vec4.z, w / vec4.w); }
		Vector4& operator/=(const Vector4& vec4) noexcept { x /= vec4.x; y /= vec4.y; z /= vec4.z; w /= vec4.w; return *this; }
		bool operator!=(const Vector4& vec4)const noexcept { return (this->x != vec4.x && this->y != vec4.y && this->z != vec4.z && this->w != vec4.w); }
		bool operator==(const Vector4& vec4)const noexcept { return (this->x == vec4.x && this->y == vec4.y && this->z == vec4.z && this->w == vec4.w); }
	};
}
