//*****************************************************************************
//* @file   Transform.h
//* @brief  トランスフォームクラス
//* @note   全てのオブジェクトの座標系を管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once

#include "macro.h"
#include "std.h"
#include "Physics.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace GAME_SYSTEMS
{
	class Transform final : public Physics
	{
	public:
		enum class Field
		{
			Position,
			Rotation,
			Scale
		};

	public:
		//Add Transform Function
		void Add(Transform::Field type, Float32 x = 0.0f, Float32 y = 0.0f, Float32 z = 0.0f);

		//Set Transform Function
		void Set(Transform::Field type, Float32 x, Float32 y, Float32 z);
	public:
		const myMath::Vector3& GetPosition() const noexcept { return m_position; }
		const myMath::Vector3& GetRotation() const noexcept { return m_rotation; }
		myMath::Matrix4x4& GetWorldMatrix() noexcept { return m_worldMatrix; }
		myMath::Vector4& GetAxisX();
		myMath::Vector4& GetAxisY();
		myMath::Vector4& GetAxisZ();


	private:
		myMath::Vector3 m_position;
		myMath::Vector3 m_rotation;
		myMath::Vector3 m_scale;

	private:
		myMath::Quaternion m_quaternion;
		myMath::Matrix4x4 m_worldMatrix;

	private:
		void SetWorldMatrix();

	public:
		Transform() : Physics("Transform", Type::Transform) {}

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;
	};
}

