//*****************************************************************************
//* @file   Camera.h
//* @brief  
//* @note   �J�����̃R���|�[�l���g
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "Camera.h"
#include "../System/Window.h"
#include "../System/DX11Settransform.h"
#include "DeveloperMenu.h"
#include "Debug.h"

USING_SYSTEMS;
USING_GAME_SYSTEMS;
USING_MY_MATH;

Int32 Camera::m_activeCameraPriority = 0;

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

void GAME_SYSTEMS::Camera::Start()
{
	m_eye.Set(-100.0f,0.0f,-100.0f);
	m_lookAt.Set(50.0f,0.0f,50.0f);
	m_up.Set(0.0f,1.0f,0.0f);

	// �N���b�v�ݒ�
	m_nearClip = 1.0f;
	m_farClip = 10000.0f;
	m_fov = DirectX::XM_PI / 2.0f;
	
	// �A�X�y�N�g�ݒ�
	Float32 screenSizeX = static_cast<Float32>(Window::GetInstance()->GetWidthSize());
	Float32 screenSizeY = static_cast<Float32>(Window::GetInstance()->GetHeightSize());
	m_aspect = screenSizeX / screenSizeY;
}


void GAME_SYSTEMS::Camera::Update()
{
	// �r���[�ϊ��s��𐶐�����
	m_viewTransformMatrix = myMath::Matrix4x4::CreateLookAtMatrix(m_eye, m_lookAt, m_up);

	// �v���W�F�N�V�����s��𐶐�����
	m_projectionTransformMatrix = myMath::Matrix4x4::CreateProjectionMatrix(m_fov, m_aspect, m_nearClip, m_farClip);

	if (m_priority >= m_activeCameraPriority)
	{
		// �J�����̗D��x���������ɃJ�����s���؂�ւ��܂�
		m_activeCameraPriority = m_priority;
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, m_viewTransformMatrix);
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, m_projectionTransformMatrix);
	}

	if (DEVELOPER::DeveloperMenu::GetType() == DEVELOPER::DeveloperMenu::Type::Develop)
	{
		TOOLS::Debug::DrawRay(m_eye, GetAxisX(), 300.0f, MY_MATH::Color::Red);
		TOOLS::Debug::DrawRay(m_eye, GetAxisY(), 300.0f, MY_MATH::Color::Green);
		TOOLS::Debug::DrawRay(m_eye, GetAxisZ(), 300.0f, MY_MATH::Color::Blue);
	}
}


void GAME_SYSTEMS::Camera::End()
{
}
