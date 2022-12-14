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
	// 有効度をエディタから取得
	m_camera->SetPriority(DeveloperMenu::GetDebugCameraPriority());
	
	// デバッグ用カメラを移動します
	Vector3 moveForce;
	auto forward = m_camera->GetForward();
	auto up = m_camera->GetUp();
	auto right = m_camera->GetRight();

	if (Keyboard::Press(Keycode::UpArrow))
	{
		moveForce.x = forward.x * m_speed;
		moveForce.y = forward.y * m_speed;
		moveForce.z = forward.z * m_speed;
	}

	if (Keyboard::Press(Keycode::DownArrow))
	{
		moveForce.x = (forward.x * -1.0f) * m_speed;
		moveForce.y = (forward.y * -1.0f) * m_speed;
		moveForce.z = (forward.z * -1.0f) * m_speed;
	}

	if (Keyboard::Press(Keycode::RightArrow))
	{
		moveForce.x = right.x * m_speed;
		moveForce.y = right.y * m_speed;
		moveForce.z = right.z * m_speed;
	}
	if (Keyboard::Press(Keycode::LeftArrow))
	{
		moveForce.x = (right.x * -1.0f) * m_speed;
		moveForce.y = (right.y * -1.0f) * m_speed;
		moveForce.z = (right.z * -1.0f) * m_speed;
	}
	DEVELOPER::DeveloperMenu::AddForceDebugCamera(moveForce);
	m_transform->m_Position = DEVELOPER::DeveloperMenu::GetDebugPosition();

	// デバッグ用カメラを回転します
	// 射影しているときのみ操作を可能にする
	if (m_camera->IsProjection() == true)
	{
		Float32 angleHorizontal = 0.0f;
		Float32 angleVertical = 0.0f;
		if (Mouse::Click(MouseCode::Right))
		{
			angleHorizontal = Mouse::CursorVelocity().x * 0.25f;
			angleVertical = Mouse::CursorVelocity().y * 0.2f;

			if (std::fabsf(angleHorizontal) >= std::fabsf(angleVertical))
			{
				m_transform->m_Rotation = m_transform->m_Rotation * Quaternion::CreateByRotationAxis(Vector3::Up, angleHorizontal);

			}
			else
			{
				m_transform->m_Rotation = m_transform->m_Rotation * Quaternion::CreateByRotationAxis(right, angleVertical);
			}

		}

	}
}

void DebugCameraMovement::End()
{
}
