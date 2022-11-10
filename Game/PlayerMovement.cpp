#include "PlayerMovement.h"

void PlayerMovement::Start()
{
}

void PlayerMovement::Update()
{
	m_moveForce.Set( 0.0f, 0.0f ,0.0f );
	
	m_moveForce.x = m_moveSpeed * GamePad::LeftStick().x;
	m_moveForce.z = m_moveSpeed * GamePad::LeftStick().y;

	// �O�ړ�
	// UnrealEngine����Export�������f���Ȃ̂�Zup�ɂȂ��Ă���
	auto trans = GetOwner()->m_transform;
	GetOwner()->m_transform->m_position.x += m_moveForce.z * trans->GetAxisY().x;
	GetOwner()->m_transform->m_position.y += m_moveForce.z * trans->GetAxisY().y;
	GetOwner()->m_transform->m_position.z += m_moveForce.z * trans->GetAxisY().z;

	// ���ړ�
	GetOwner()->m_transform->m_position.x += m_moveForce.x * trans->GetAxisX().x;
	GetOwner()->m_transform->m_position.y += m_moveForce.x * trans->GetAxisX().y;
	GetOwner()->m_transform->m_position.z += m_moveForce.x * trans->GetAxisX().z;


}

void PlayerMovement::End()
{
}
