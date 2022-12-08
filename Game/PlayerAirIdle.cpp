#include "PlayerAirIdle.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"

USING_MY_MATH;

void PlayerAirIdle::EnterState()
{
	m_owner->GetAnimator()->Play("AirMove");

	// •‚‚­‚‚³Ý’è
	m_startPosition = m_owner->GetOwner()->m_transform->m_Position;
	m_endPosition.x = m_startPosition.x;
	m_endPosition.y = m_startPosition.y + m_owner->GetAirHeight();
	m_endPosition.z = m_startPosition.z;

	m_counter = 0;
	
	m_isRiseUp = false;
	if (m_owner->GetStateMachine().GetBeforeName() == "MoveAir")
	{
		m_isRiseUp = true;
	}
}

void PlayerAirIdle::ExitState()
{
}

void PlayerAirIdle::Update()
{
	auto transform = m_owner->GetOriginTransform();
	// •‚‚­
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
		// ã¸
		transform->m_Position = Vector3::Larp(m_startPosition, m_endPosition, larpParam);
	}
	else
	{
		if (GamePad::LeftTrigger() >= GamePad::m_XinputTriggerMax &&
			GamePad::OldLeftTrigger() != GamePad::m_XinputTriggerMax)
		{
			// ’n–ÊˆÚ“®‚ÉØ‚è‘Ö‚¦
			m_owner->GetStateMachine().ChangeState("Fall");
			return;
		}
		else if (GamePad::RightTrigger() >= GamePad::m_XinputTriggerMax &&
			GamePad::OldRightTrigger() != GamePad::m_XinputTriggerMax)
		{
			// ‹ó’†ˆÚ“®
			m_owner->GetStateMachine().ChangeState("MoveAir");
			return;
		}
	}
	m_counter++;
}
