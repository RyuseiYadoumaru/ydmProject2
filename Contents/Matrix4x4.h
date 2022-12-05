//*****************************************************************************
//!	@file	Matrix4x4.h
//!	@brief	3D行列クラス　4*4
//!	@note	3D行列関連
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#include <DirectXMath.h>
#include <assimp\Importer.hpp>
#include "std.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"


enum class HandType
{
	Left,
	Right
};

namespace myMath
{
	class Matrix4x4 : public DirectX::XMFLOAT4X4
	{
	public:
		static Matrix4x4 MatrixMultiply(Matrix4x4& mtx1, Matrix4x4& mtx2) noexcept;
		static Matrix4x4 CreateMatrixIdentity() noexcept;
		static Matrix4x4 CreateTransposeMatrix(const Matrix4x4& mtx) noexcept;
		
		static Matrix4x4 CreateWorldMatrix(Vector3& position, Vector3& rotation, Vector3 scale) noexcept;
		static Matrix4x4 CreateWorldMatrix(Matrix4x4& position, Matrix4x4& rotation, Matrix4x4& scale) noexcept;

		static Matrix4x4 CreateLookAtMatrix(Vector3& eye, Vector3& lookat, Vector3& up, HandType type = HandType::Left);
		static Matrix4x4 CreateProjectionMatrix(Float32 fov, Float32 aspect, Float32 nearClip, Float32 farClip, HandType type = HandType::Left);

		static Matrix4x4 CreateTranslationMatrix(const Vector3& vector3);

		static Matrix4x4 CreateMatrixFromQuaternion(Quaternion quaternion) noexcept;

		static Matrix4x4 CreateRotationMatrix(Float32 x, Float32 y, Float32 z) noexcept;
		static Matrix4x4 CreateRotationXMatrix(Float32 rotationX);
		static Matrix4x4 CreateRotationYMatrix(Float32 rotationY);
		static Matrix4x4 CreateRotationZMatrix(Float32 rotationZ);

		static Matrix4x4 CreateMatrixFromAIMatrix(aiMatrix4x4& aiMtx);

	public:
		void Set(DirectX::XMMATRIX& matrix) noexcept { DirectX::XMStoreFloat4x4(this, matrix); }
		void Set(DirectX::XMFLOAT4X4 matrix) noexcept
		{
			_11 = matrix._11; _12 = matrix._12; _13 = matrix._13; _14 = matrix._14;
			_21 = matrix._21; _22 = matrix._22; _23 = matrix._23; _24 = matrix._24;
			_31 = matrix._31; _32 = matrix._32; _33 = matrix._33; _34 = matrix._34;
			_41 = matrix._41; _42 = matrix._42; _43 = matrix._43; _44 = matrix._44;
		}

		DirectX::XMMATRIX GetXMMatrix() noexcept { return DirectX::XMLoadFloat4x4(this); }
		Vector4 GetQuaternion() noexcept;

	public:
		Matrix4x4() = default;
		~Matrix4x4() = default;
		Matrix4x4& operator=(const Matrix4x4&) = default;


	};
}