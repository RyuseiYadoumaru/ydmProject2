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
		static myMath::Vector3 RotationMatrixToEuler(const myMath::Matrix4x4& rotMtx);

	public:
		myMath::Vector3		m_Position;
		myMath::Quaternion  m_Rotation;
		myMath::Vector3		m_Scale;

	public:
		void SetRotation(Float32 x, Float32 y, Float32 z) noexcept;
		myMath::Vector3 GetEulerAngles() noexcept;
		const myMath::Vector3& GetPosition() const noexcept { return m_Position; }
		const myMath::Quaternion& GetRotation() const noexcept { return m_Rotation; }
		const myMath::Vector3& GetScale() const noexcept { return m_Scale; }

		myMath::Matrix4x4& GetWorldMatrix() noexcept { return m_worldMatrix; }

		myMath::Vector4 GetAxisX();
		myMath::Vector4 GetAxisY();
		myMath::Vector4 GetAxisZ();

	private:
		myMath::Matrix4x4 m_worldMatrix;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		explicit Transform() : 
			Physics("Transform", Type::Transform),
			m_Position(0.0f, 0.0f, 0.0f),
			m_Rotation(myMath::Quaternion::CreateByRotation(0.0f, 0.0f, 0.0f)),
			m_Scale(1.0f, 1.0f, 1.0f) {}
		Transform(Transform&) = default;
		~Transform() = default;
	};
}

