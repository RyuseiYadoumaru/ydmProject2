//*****************************************************************************
//* @file   Camera.h
//* @brief  
//* @note   カメラのコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "Graphics.h"

#include "Vector3.h"
#include "Matrix4x4.h"

namespace GAME_SYSTEMS
{
	class Transform;
	class Camera : public Graphics
	{
	public:
		static void CommonUpdate();

	private:
		static Int32 m_activeCameraPriority;

	public:
		// カメラの優先度
		void SetPriority(Int32 priority) noexcept { m_priority = priority; }
		const Int32& GetPriority() const noexcept { return m_priority; }

		// カメラ向き
		MY_MATH::Vector3 GetAxisX() noexcept;
		MY_MATH::Vector3 GetAxisY() noexcept;
		MY_MATH::Vector3 GetAxisZ() noexcept;

		MY_MATH::Vector3 GetRight() const noexcept 
		{
			return MY_MATH::Vector3(m_viewTransformMatrix._11, m_viewTransformMatrix._21, m_viewTransformMatrix._31); 
		}
		MY_MATH::Vector3 GetForward() const noexcept
		{
			return MY_MATH::Vector3(m_viewTransformMatrix._13 * -1.0f, m_viewTransformMatrix._23 * -1.0f, m_viewTransformMatrix._33 * -1.0f);
		}
		MY_MATH::Vector3 GetUp() const noexcept
		{
			return MY_MATH::Vector3(m_viewTransformMatrix._12, m_viewTransformMatrix._22, m_viewTransformMatrix._32);
		}

	private:
		myMath::Vector3 m_eye;
		myMath::Vector3 m_lookAt;
		myMath::Vector3 m_up;

		Float32 m_nearClip	= 0.0f;
		Float32 m_farClip	= 0.0f;
		Float32 m_aspect	= 0.0f;
		Float32 m_fov		= 0.0f;

		myMath::Matrix4x4 m_projectionTransformMatrix;
		myMath::Matrix4x4 m_viewTransformMatrix;
		
		Int32 m_priority	= 1;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	private:
		SharedPtr<Transform> m_transform;

	public:
		Camera() : Graphics("Camera", Graphics::Type::Camera){}
		~Camera() = default;
	};
}
