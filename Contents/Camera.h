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
	class Camera : public Graphics
	{
	public:
		// カメラの優先度
		void SetPriority(Int32 priority) noexcept { m_priority = priority; }

	private:
		static Int32 m_activeCameraPriority;

	private:
		myMath::Matrix4x4 m_projectionMatrix;
		myMath::Matrix4x4 m_cameraMatrix;

		myMath::Vector3 m_eye;
		myMath::Vector3 m_lookAt;
		myMath::Vector3 m_up;

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
