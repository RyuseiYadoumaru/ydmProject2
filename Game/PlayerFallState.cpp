#include "GameContents.h"
#include "Player.h"
#include "PlayerMovement.h"
#include "PlayerFallState.h"

void PlayerFallState::EnterState()
{
}

void PlayerFallState::ExitState()
{
}

void PlayerFallState::Update()
{
	auto transform = m_owner->GetOwner()->m_transform;
	
	// —Ž‰ºˆ—
	 transform->m_position.y -= 10.0f;

	if (transform->m_position.y <= 0.0f)
	{
		m_owner->GetStateMachine().ChangeState("MoveGround");
		transform->m_position.y = 0.0f;
		return;
	}
}

