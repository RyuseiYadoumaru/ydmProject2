#include "PlayerActionCamera.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"

//#include "GameContents.h"

#include "Camera.h"
#include "Transform.h"

USING_GAME_SYSTEMS;
USING_MY_MATH;
USING_TOOLS;

void PlayerActionCamera::FocusObject()
{
	// 中心座標取得
	Float32 centerPositionX = m_focusTransform->GetPosition().x;
	Float32 centerPositionZ = m_focusTransform->GetPosition().z;

	// 度数法を弧度法に変換する
	Float32 horizontalRadian = m_horizontalAngle * 3.14f / 180.0f;
	Float32 verticalRadian = m_verticalAngle * 3.14f / 180.0f;

	// フォーカースオブジェクトの中心座標からの円状の位置
	Float32 addPositionX = sin(horizontalRadian) * m_horizontalRadius;
	Float32 addPositionY = sin(verticalRadian) * m_verticalRadius;
	Float32 addPositionZ = cos(horizontalRadian) * m_horizontalRadius;
	//m_camera->m_eye.Set(
	//	m_focusTransform->GetPosition().x + addPositionX,
	//	m_focusTransform->GetPosition().y + addPositionY + m_heightOffset,
	//	m_focusTransform->GetPosition().z + addPositionZ);

	// 注視点をフォーカスオブジェクトに向ける
	//m_camera->m_lookAt.Set(
	//	m_focusTransform->GetPosition().x,
	//	m_focusTransform->GetPosition().y,
	//	m_focusTransform->GetPosition().z);
	//m_camera->m_lookAt += m_lookAtOffset;

	// カメラの上ベクトルをフォーカスオブジェクトに同期
	//m_camera->m_up.Set(
	//	m_focusTransform->GetAxisY().x,
	//	m_focusTransform->GetAxisY().y,
	//	m_focusTransform->GetAxisY().z);
}

void PlayerActionCamera::Start()
{
	m_trackingPlayer = GameObjectManager::GetInstance()->Find("Player");
	Debug::Assert(m_trackingPlayer == nullptr);
	m_camera = GetOwner()->GetComponent<gameSystems::Camera>();
	Debug::Assert(m_camera == nullptr);

	m_focusTransform = m_trackingPlayer->GetComponent<gameSystems::Transform>();
	Debug::Assert(m_focusTransform == nullptr);
	// プレイヤー移動スクリプトを取得
	m_playerMovement = m_trackingPlayer->GetComponent<PlayerMovement>();
	Debug::Assert(m_playerMovement == nullptr);

	m_lookAtOffset.Set(0.0f, 100.0f, 0.0f);

	// フォーカスオブジェクトの向いてる方向にカメラアングルをセットする
	m_horizontalAngle = m_focusTransform->GetRotation().y;
	FocusObject();

	// 振動幅
	m_saveRightVector = m_camera->GetAxisX();

	GetOwner()->m_transform->m_Position.Set(00.0f, 0.0f, 0.0f);

}

void PlayerActionCamera::Update()
{
	FocusObject();
	Vector2 moveForce = { 0.0f, 0.0f };
	auto transform = GetOwner()->m_transform;

	TOOLS::Debug::DrawAxis(transform->m_Position, m_camera->GetForward(), 100.0f, Color::Yellow);

	if (m_playerMovement->IsHitStop() == true)
	{
		m_hitStopVibrationRange *= -1.0f;
		//m_camera->m_eye.x += m_hitStopVibrationRange * m_saveRightVector.x;
		//m_camera->m_eye.y += m_hitStopVibrationRange * m_saveRightVector.y;
		//m_camera->m_eye.z += m_hitStopVibrationRange * m_saveRightVector.z;
		return;
	}
	else
	{
		m_saveRightVector = m_camera->GetAxisX();
	}

	if (m_isReset == true)
	{
		m_totalDeltaTime += Timer::FixDeltaTime();
		if (m_totalDeltaTime >= m_resetTime)
		{
			m_totalDeltaTime = m_resetTime;
			m_isReset = false;
		}
		m_horizontalAngle = Easing::SineOut(m_totalDeltaTime, m_resetTime, m_resetStartAngle, m_resetTargetAngle);
	}
	else
	{
		//if (GamePad::Trigger(Xinput::Y))
		//{
		//	auto eulerAngile = Quaternion::EulerAngles(m_focusTransform->m_Rotation);
		//	if (m_horizontalAngle != eulerAngile.z)
		//	{
		//		m_resetTargetAngle = eulerAngile.z;
		//		if (m_horizontalAngle - m_resetTargetAngle > 180.0f) m_resetTargetAngle += 360.0f;
		//		m_resetStartAngle = m_horizontalAngle;
		//		m_totalDeltaTime = 0.0f;
		//		m_isReset = true;
		//	}
		//}
		moveForce.x = m_movevSensitivity * GamePad::RightStick().x;
		moveForce.y = m_movevSensitivity * GamePad::RightStick().y;

		m_horizontalAngle += moveForce.x;
		m_verticalAngle += moveForce.y;

		if (m_horizontalAngle < 0)
		{
			m_horizontalAngle += 360.0f;
		}
		if (m_horizontalAngle >= 360.0f)
		{
			m_horizontalAngle -= 360.0f;
		}

		// 縦の移動が最大
		if (m_verticalAngle > m_limitVerticalAngle)
		{
			m_verticalAngle = m_limitVerticalAngle;
		}
		else if (m_verticalAngle < -m_limitVerticalAngle)
		{
			m_verticalAngle = -m_limitVerticalAngle;
		}
	}
}

void PlayerActionCamera::End()
{
}
