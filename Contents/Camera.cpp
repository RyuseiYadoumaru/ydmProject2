//*****************************************************************************
//* @file   Camera.h
//* @brief  
//* @note   カメラのコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "Camera.h"
#include "../System/Window.h"
#include "../DX11Settransform.h"

USING_SYSTEMS;
USING_GAME_SYSTEMS;

Int32 Camera::m_activeCameraPriority = 0;

void GAME_SYSTEMS::Camera::Start()
{
	m_eye.Set(0.0f,100.0f,-300.0f);
	m_lookAt.Set(0.0f,100.0f,0.0f);
	m_up.Set(0.0f,1.0f,0.0f);

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
	// カメラ行列を生成する
	m_cameraMatrix = myMath::Matrix4x4::CreateLookAtMatrix(m_eye, m_lookAt, m_up);

	// プロジェクション行列を生成する
	m_projectionMatrix = myMath::Matrix4x4::CreateProjectionMatrix(m_fov, m_aspect, m_nearClip, m_farClip);

	if (m_priority >= m_activeCameraPriority)
	{
		// カメラの優先度が高い時にカメラ行列を切り替えます
		m_activeCameraPriority = m_priority;
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, m_cameraMatrix);
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, m_projectionMatrix);
	}
}


void GAME_SYSTEMS::Camera::End()
{
}
