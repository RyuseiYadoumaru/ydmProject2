//*****************************************************************************
//* @file   Camera.h
//* @brief  
//* @note   カメラのコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "../System/Window.h"
#include "../System/DX11Settransform.h"
#include "DeveloperMenu.h"
#include "Debug.h"

USING_SYSTEMS;
USING_GAME_SYSTEMS;
USING_MY_MATH;

Int32 Camera::m_activeCameraPriority = 0;
GAME_SYSTEMS::Camera* Camera::m_activeCamera = nullptr;

MY_MATH::Vector3 GAME_SYSTEMS::Camera::GetAxisX() noexcept
{
	Vector3 outVec;
	outVec.x = m_viewTransformMatrix._11;
	outVec.y = m_viewTransformMatrix._21;
	outVec.z = m_viewTransformMatrix._31;
	return outVec;
}

MY_MATH::Vector3 GAME_SYSTEMS::Camera::GetAxisY() noexcept
{
	Vector3 outVec;
	outVec.x = m_viewTransformMatrix._12;
	outVec.y = m_viewTransformMatrix._22;
	outVec.z = m_viewTransformMatrix._32;
	return outVec;
}

MY_MATH::Vector3 GAME_SYSTEMS::Camera::GetAxisZ() noexcept
{
	Vector3 outVec;
	outVec.x = m_viewTransformMatrix._13;
	outVec.y = m_viewTransformMatrix._23;
	outVec.z = m_viewTransformMatrix._33;
	return outVec;
}

void GAME_SYSTEMS::Camera::CommonUpdate()
{
	m_activeCamera = nullptr;
	m_activeCameraPriority = NULL;
}

void GAME_SYSTEMS::Camera::Start()
{
	// トランスフォーム取得
	m_transform = GetOwner()->m_transform;

	// クリップ設定
	m_nearClip = 1.0f;
	m_farClip = 10000.0f;
	m_fov = DirectX::XM_PI / 2.0f;
	
	// アスペクト設定
	Float32 screenSizeX = static_cast<Float32>(Window::GetInstance()->GetWidthSize());
	Float32 screenSizeY = static_cast<Float32>(Window::GetInstance()->GetHeightSize());
	m_aspect = screenSizeX / screenSizeY;
}


void GAME_SYSTEMS::Camera::Update()
{
	// トランスフォームからカメラ行列を生成
	m_viewTransformMatrix = Transform::CreateViewMatrix(*m_transform);
	m_isProjection = false;

	// Transformからカメラ情報を取得
	m_eye = m_transform->m_Position;
	m_up = GetUp();
	m_lookAt = m_eye + (m_eye * GetForward());

	// プロジェクション行列を生成する
	m_projectionTransformMatrix = myMath::Matrix4x4::CreateProjectionMatrix(m_fov, m_aspect, m_nearClip, m_farClip);

	if (m_priority >= m_activeCameraPriority || m_activeCameraPriority == NULL)
	{
		// カメラの優先度が高い時にカメラ行列を切り替えます
		if (m_activeCamera != nullptr)
		{
			m_activeCamera->m_isProjection = false;
		}
		m_isProjection = true;
		m_activeCamera = this;
		m_activeCameraPriority = m_priority;
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, m_viewTransformMatrix);
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, m_projectionTransformMatrix);
	}

	if (DEVELOPER::DeveloperMenu::GetType() == DEVELOPER::DeveloperMenu::Type::Develop)
	{
		TOOLS::Debug::DrawAxis(m_eye, GetRight(), 100.0f, MY_MATH::Color::Red);
		TOOLS::Debug::DrawAxis(m_eye, GetUp(), 100.0f, MY_MATH::Color::Green);
		TOOLS::Debug::DrawAxis(m_eye, GetForward(), 100.0f, MY_MATH::Color::Blue);
	}
}


void GAME_SYSTEMS::Camera::End()
{
}
