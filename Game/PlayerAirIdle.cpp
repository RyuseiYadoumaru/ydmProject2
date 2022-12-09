#include "PlayerAirIdle.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"

USING_MY_MATH;

void PlayerAirIdle::EnterState()
{
	// �󒆃A�j���[�V�����Đ�
	m_owner->GetAnimator()->Play("AirMove");
	m_counter = 0;

	auto transform = m_owner->GetOwner()->m_transform;
	// �󒆈ړ����󒆑ҋ@���̏�����
	if (m_owner->GetStateMachine().GetBeforeName() == "MoveAir")
	{
		// ���ݎp��
		m_startQt = m_owner->GetOwner()->m_transform->m_Rotation;

		// �A�C�h���p���쐬
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
		// ���������ݒ�
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
	// ����
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
		// �㏸
		transform->m_Position = Vector3::Larp(m_startPosition, m_endPosition, larpParam);
	}
	else
	{
		tools::Debug::DrawAxis(transform->m_Position, transform->GetAxisX(), 200.0f, Color::Yellow);
		// �A�C�h����Ԃ���Ȃ��Ƃ��͉�]�ŃA�C�h���̎p���ɖ߂��܂�
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
			// �A�C�h����ԂɂȂ��ă{�^�����삪�ł���
			if (GamePad::LeftTrigger() >= GamePad::m_XinputTriggerMax &&
				GamePad::OldLeftTrigger() != GamePad::m_XinputTriggerMax)
			{
				// �n�ʈړ��ɐ؂�ւ�
				m_owner->GetStateMachine().ChangeState("Fall");
				return;
			}
			else if (GamePad::RightTrigger() >= GamePad::m_XinputTriggerMax &&
				GamePad::OldRightTrigger() != GamePad::m_XinputTriggerMax)
			{
				// �󒆈ړ�
				m_owner->GetStateMachine().ChangeState("MoveAir");
				return;
			}
		}
	}
	m_counter++;
}
