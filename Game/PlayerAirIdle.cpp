#include "PlayerAirIdle.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"

USING_MY_MATH;

void PlayerAirIdle::EnterState()
{
	// 空中アニメーション再生
	m_owner->GetAnimator()->Play("AirMove");
	m_counter = 0;

	auto transform = m_owner->GetOwner()->m_transform;
	// 空中移動→空中待機時の初期化
	if (m_owner->GetStateMachine().GetBeforeName() == "MoveAir")
	{
		// 現在姿勢
		m_startQt = m_owner->GetOwner()->m_transform->m_Rotation;

		// アイドル姿勢作成
		//Vector3 playerUp;
		//playerUp = transform->GetAxisZ();
		//playerUp = Vector3::Normalize(playerUp);
		//Float32 angle = Vector3::Dot(Vector3::Up, playerUp) * -1.0f;
		//Vector3 rightAxis = Vector3::Cross(Vector3::Up, playerUp);
		//Vector4 axis;
		//axis = rightAxis;
		//Quaternion qtRight = Quaternion::CreateByRotationAxis(axis, Math::RadiansToDegrees(angle));
		//m_endQt = m_startQt * qtRight;

		m_isRiseUp = true;
		m_isIdling = false;
	}
	else
	{
		// 浮く高さ設定
		m_startPosition = m_owner->GetOwner()->m_transform->m_Position;
		m_endPosition.x = m_startPosition.x;
		m_endPosition.y = m_startPosition.y + m_owner->GetAirHeight();
		m_endPosition.z = m_startPosition.z;
		
		m_isRiseUp = false;
		m_isIdling = true;

	}
}

void PlayerAirIdle::ExitState()
{
	m_endQt = m_owner->GetOwner()->m_transform->m_Rotation;
}

void PlayerAirIdle::Update()
{
	//auto transform = m_owner->GetOriginTransform();
	auto transform = m_owner->GetOwner()->m_transform;
	// 浮く
	if (m_isRiseUp == false)
	{
		uInt32 time = m_owner->GetAirFrameCount();
		auto larpParam = Easing::SineOut(static_cast<Float32>(m_counter), static_cast<Float32>(time), 0.0f, 1.0f);
		if (m_counter >= time)
		{
			m_counter = 0;
			larpParam = 1;
			m_isRiseUp = true;
		}
		// 上昇
		transform->m_Position = Vector3::Larp(m_startPosition, m_endPosition, larpParam);
	}
	else
	{
		tools::Debug::DrawAxis(transform->m_Position, transform->GetAxisX(), 200.0f, Color::Yellow);
		// アイドル状態じゃないときは回転でアイドルの姿勢に戻します
		if (m_isIdling == false)
		{
			Float32 slerp = Easing::ExpoOut(static_cast<Float32>(m_counter), static_cast<Float32>(m_owner->GetAirIdleResetFrame()), 0.1f, 1.0f);
			if (m_counter >= m_owner->GetAirIdleResetFrame())
			{
				slerp = 1.0f;
				m_counter = 0;
				m_isIdling = true;
			}
			auto slerpQt = Quaternion::Slerp(m_startQt, m_endQt, slerp);
			transform->m_Rotation = slerpQt;
		}
		else
		{
			// アイドル状態になってボタン操作ができる
			if (GamePad::LeftTrigger() >= GamePad::m_XinputTriggerMax &&
				GamePad::OldLeftTrigger() != GamePad::m_XinputTriggerMax)
			{
				// 地面移動に切り替え
				m_owner->GetStateMachine().ChangeState("Fall");
				return;
			}
			else if (GamePad::RightTrigger() >= GamePad::m_XinputTriggerMax &&
				GamePad::OldRightTrigger() != GamePad::m_XinputTriggerMax)
			{
				// 空中移動
				m_owner->GetStateMachine().ChangeState("MoveAir");
				return;
			}
		}
	}
	m_counter++;
}
