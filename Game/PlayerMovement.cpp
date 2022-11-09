#include "PlayerMovement.h"

void PlayerMovement::Start()
{
}

void PlayerMovement::Update()
{
	m_moveForce.Set( 0.0f, 0.0f ,0.0f );
	
	m_moveForce.x = m_moveSpeed * GamePad::LeftStick().x;
	m_moveForce.z = m_moveSpeed * GamePad::LeftStick().y;

	GetOwner()->m_transform->m_position += m_moveForce;
}

void PlayerMovement::End()
{
}
