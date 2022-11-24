#include "MoveMentSphere.h"

void MoveMentSphere::Start()
{
	m_generator = GameObjectManager::GetInstance()->Find("EnemyGenerator");
	GetOwner()->m_transform->m_position = m_generator->m_transform->m_position;
	GetOwner()->m_transform->m_rotation = m_generator->m_transform->m_rotation;

}

void MoveMentSphere::Update()
{
	// 移動
	auto trans = GetOwner()->m_transform;
	GetOwner()->m_transform->m_position.x += -m_moveForce * trans->GetAxisZ().x;
	GetOwner()->m_transform->m_position.y += -m_moveForce * trans->GetAxisZ().y;
	GetOwner()->m_transform->m_position.z += -m_moveForce * trans->GetAxisZ().z;
	
	// 移動量決め
	m_moveForce = 0.0f;

	m_moveForce = m_speed;

	// 生存時間
	if (m_timer >= m_survivalTime)
	{
		auto ownerId = GetOwner()->GetID();
		GameObjectManager::GetInstance()->Destroy(GameObjectManager::GetInstance()->Find(ownerId));
	}

	m_timer += Timer::DeltaTime();
}

void MoveMentSphere::End()
{
}
