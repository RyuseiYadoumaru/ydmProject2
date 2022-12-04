//*****************************************************************************
//* @file   Camera.h
//* @brief  
//* @note   �J�����̃R���|�[�l���g
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
	class Camera : public Graphics
	{
	public:
		myMath::Vector3 m_eye;
		myMath::Vector3 m_lookAt;
		myMath::Vector3 m_up;

	public:
		// �J�����̗D��x
		void SetPriority(Int32 priority) noexcept { m_priority = priority; }
		const Int32& GetPriority() const noexcept { return m_priority; }

		// �J��������
		MY_MATH::Vector3 GetAxisX() noexcept;
		MY_MATH::Vector3 GetAxisY() noexcept;
		MY_MATH::Vector3 GetAxisZ() noexcept;


	private:
		static Int32 m_activeCameraPriority;

	private:
		myMath::Matrix4x4 m_projectionTransformMatrix;
		myMath::Matrix4x4 m_viewTransformMatrix;

		Float32 m_nearClip	= 0.0f;
		Float32 m_farClip	= 0.0f;
		Float32 m_aspect	= 0.0f;
		Float32 m_fov		= 0.0f;

		Int32 m_priority	= 1;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		Camera() : Graphics("Camera", Graphics::Type::Camera){}
		~Camera() = default;
	};
}
