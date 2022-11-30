#include "ThirdPersonCamera.h"
#include "PlayerMovement.h"
USING_TOOLS;

void ThirdPersonCamera::FocusObject()
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
	m_camera->m_eye.Set(
		m_focusTransform->GetPosition().x + addPositionX,
		m_focusTransform->GetPosition().y + addPositionY + m_heightOffset,
		m_focusTransform->GetPosition().z + addPositionZ
	);

	// 注視点をフォーカスオブジェクトに向ける
	m_camera->m_lookAt.Set(
		m_focusTransform->GetPosition().x,
		m_focusTransform->GetPosition().y,
		m_focusTransform->GetPosition().z
	);
	m_camera->m_lookAt += m_lookAtOffset;

	// カメラの上ベクトルをフォーカスオブジェクトに同期
	//m_camera->m_up.Set(
	//	m_focusTransform->GetAxisY().x,
	//	m_focusTransform->GetAxisY().y,
	//	m_focusTransform->GetAxisY().z);

}

void ThirdPersonCamera::Start()
{
	m_focusObject = GameObjectManager::GetInstance()->Find("Player");
	Debug::Assert(m_focusObject == nullptr);
	m_focusTransform = m_focusObject->GetComponent<Transform>();
	Debug::Assert(m_focusTransform == nullptr);
	m_camera = GetOwner()->GetComponent<Camera>();
	Debug::Assert(m_camera == nullptr);

	m_lookAtOffset.Set( 0.0f, 30.0f, 0.0f );

	// フォーカスオブジェクトの向いてる方向にカメラアングルをセットする
	m_horizontalAngle = m_focusTransform->GetRotation().y;
	FocusObject();
}

void ThirdPersonCamera::Update()
{
	FocusObject();
	Vector2 moveForce = { 0.0f, 0.0f };
	
	if (m_isReset == true)
	{
		m_totalDeltaTime += Timer::DeltaTime();
		if (m_totalDeltaTime >= m_resetTime)
		{
			m_totalDeltaTime = m_resetTime;
			m_isReset = false;
		}
		m_horizontalAngle = Easing::SineOut(m_totalDeltaTime, m_resetTime, m_resetStartAngle, m_resetTargetAngle);
	}
	else
	{
		if (GamePad::Trigger(Xinput::Y))
		{
			if (m_horizontalAngle != m_focusTransform->GetRotation().y)
			{
				m_resetTargetAngle = m_focusTransform->GetRotation().y;
				if (m_horizontalAngle - m_resetTargetAngle > 180.0f) m_resetTargetAngle += 360.0f;
				m_resetStartAngle = m_horizontalAngle;
				m_totalDeltaTime = 0.0f;
				m_isReset = true;
			}
		}
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

		if (m_verticalAngle > m_limitVerticalAngle) m_verticalAngle = m_limitVerticalAngle;
		if (m_verticalAngle < -m_limitVerticalAngle) m_verticalAngle = -m_limitVerticalAngle;

	}
}

void ThirdPersonCamera::End()
{
}
