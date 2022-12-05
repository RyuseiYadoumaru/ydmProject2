#include "DebugCameraMovement.h"

USING_GAME_SYSTEMS;
USING_MY_MATH;


void DebugCameraMovement::Start()
{
	TOOLS::Debug::Assert(m_debugCamera == nullptr);
	m_camera = m_debugCamera->GetComponent<Camera>();
	TOOLS::Debug::Assert(m_camera == nullptr);
}

void DebugCameraMovement::Update()
{
	Vector3 moveForce;

	if (Keyboard::Press(Keycode::W))
	{
		moveForce.x = m_camera->GetAxisZ().x * m_speed;
		moveForce.y = m_camera->GetAxisZ().y * m_speed;
		moveForce.z = m_camera->GetAxisZ().z * m_speed;
	}

	if (Keyboard::Press(Keycode::S))
	{
		moveForce.x = m_camera->GetAxisZ().x * m_speed * -1.0f;
		moveForce.y = m_camera->GetAxisZ().y * m_speed * -1.0f;
		moveForce.z = m_camera->GetAxisZ().z * m_speed * -1.0f;
	}

	if (Keyboard::Press(Keycode::UpArrow))
	{
		moveForce.x = m_camera->GetAxisY().x * m_speed;
		moveForce.y = m_camera->GetAxisY().y * m_speed;
		moveForce.z = m_camera->GetAxisY().z * m_speed;
	}
	if (Keyboard::Press(Keycode::DownArrow))
	{
		moveForce.x = m_camera->GetAxisY().x * m_speed * -1.0f;
		moveForce.y = m_camera->GetAxisY().y * m_speed * -1.0f;
		moveForce.z = m_camera->GetAxisY().z * m_speed * -1.0f;
	}


	m_camera->m_lookAt += moveForce;
	m_camera->m_eye += moveForce;
}

void DebugCameraMovement::End()
{
}
