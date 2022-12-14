#include "DebugCameraMovement.h"
#include "DeveloperMenu.h"

USING_GAME_SYSTEMS;
USING_DEVELOPER;
USING_MY_MATH;


void DebugCameraMovement::Start()
{
	TOOLS::Debug::Assert(m_debugCamera == nullptr);
	m_camera = m_debugCamera->GetComponent<Camera>();
	TOOLS::Debug::Assert(m_camera == nullptr);
	m_transform = GetOwner()->m_transform.get();
}

void DebugCameraMovement::Update()
{
	Vector3 moveForce;
	Float32 angle = 0.0f;
	if (Keyboard::Press(Keycode::F4))
	{
		angle += 5.0f;
	}
	if (Keyboard::Press(Keycode::F3))
	{
		angle -= 5.0f;
	}
	GetOwner()->m_transform->m_Rotation = GetOwner()->m_transform->m_Rotation * Quaternion::CreateByRotationAxis(Vector3::Up, angle);


	m_camera->SetPriority(DeveloperMenu::GetDebugCameraPriority());
	auto forward = m_camera->GetForward();

	if (Keyboard::Press(Keycode::W))
	{
		moveForce.x = forward.x * m_speed;
		moveForce.y = forward.y * m_speed;
		moveForce.z = forward.z * m_speed;
	}

	if (Keyboard::Press(Keycode::S))
	{
		moveForce.x = (forward.x * -1.0f) * m_speed;
		moveForce.y = (forward.y * -1.0f) * m_speed;
		moveForce.z = (forward.z * -1.0f) * m_speed;
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

	m_transform->m_Position += moveForce;
	//m_camera->m_lookAt += moveForce;
	//m_camera->m_eye += moveForce;
}

void DebugCameraMovement::End()
{
}
