#include "GameContents.h"
#include "PlayerMoveAir.h"
#include "PlayerMovement.h"

void PlayerMoveAir::EnterState()
{
	m_canAirMove = false;
	// ���������ݒ�
	m_startPosition = m_owner->GetOwner()->m_transform->m_position;
	m_endPosition.x = m_startPosition.x;
	m_endPosition.y = m_startPosition.y + m_owner->GetAirHeight();
	m_endPosition.z = m_startPosition.z;

	m_counter = 0;
}

void PlayerMoveAir::ExitState()
{
}

void PlayerMoveAir::Update()
{
	auto transform = m_owner->GetOwner()->m_transform;

	if (m_canAirMove == true)
	{
		m_owner->GetStateMachine().ChangeState("MoveGround");
		return;
	}

	// �����Ă���i�K
	else
	{
		// ����
		uInt32 time = m_owner->GetAirFrameCount();
		auto larpParam = Easing::SineOut(static_cast<Float32>(m_counter), static_cast<Float32>(time), 0.0f, 1.0f);
		if (m_counter >= time)
		{
			larpParam = 1.0f;
			m_canAirMove = true;
			m_counter = 0;
		}

		// �㏸
		transform->m_position = Vector3::Larp(m_startPosition, m_endPosition, larpParam);
	}

	// �g�[�^���^�C�����Z
	m_counter++;

}
