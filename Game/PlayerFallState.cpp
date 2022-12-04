#include "GameContents.h"
#include "Player.h"
#include "PlayerMovement.h"
#include "PlayerFallState.h"

void PlayerFallState::EnterState()
{
	m_counter = 5;
}

void PlayerFallState::ExitState()
{
}

void PlayerFallState::Update()
{
	m_counter++;
	// —Ž‰ºˆ—
	auto transform = m_owner->GetOwner()->m_transform;
	Float32 scale = Easing::SineIn(static_cast<Float32>(m_counter), static_cast<Float32>(m_owner->GetMaxFallSpeedFrame()), 0.0f, 1.0f);
	transform->m_position.y -= m_owner->GetMaxFallSpeed() * scale;

	if (transform->m_position.y <= 0.0f)
	{
		m_owner->GetStateMachine().ChangeState("MoveGround");
		transform->m_position.y = 0.0f;
		return;
	}
}

