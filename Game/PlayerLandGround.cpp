#include "PlayerLandGround.h"
#include "PlayerMovement.h"

void PlayerLandGround::EnterState()
{
	m_owner->GetAnimator()->Play("LandGround");
	m_counter = 0;
}

void PlayerLandGround::ExitState()
{
}

void PlayerLandGround::Update()
{
	m_counter++;
	if (m_counter >= m_owner->GetLandStopFrame())
	{
		m_owner->GetStateMachine().ChangeState("MoveGround");
		return;
	}
}
