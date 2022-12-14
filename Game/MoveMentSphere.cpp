#include "MoveMentSphere.h"

void MoveMentSphere::Start()
{
	m_generator = GameObjectManager::GetInstance()->Find("EnemyGenerator");
	GetOwner()->m_transform->m_Position = m_generator->m_transform->m_Position;
	GetOwner()->m_transform->m_Rotation = m_generator->m_transform->m_Rotation;

}

void MoveMentSphere::Update()
{
	// 移動
	auto trans = GetOwner()->m_transform;
	GetOwner()->m_transform->m_Position.x += -m_moveForce * trans->GetAxisZ().x;
	GetOwner()->m_transform->m_Position.y += -m_moveForce * trans->GetAxisZ().y;
	GetOwner()->m_transform->m_Position.z += -m_moveForce * trans->GetAxisZ().z;
	
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
