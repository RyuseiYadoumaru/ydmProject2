#include "EnemyGenerator.h"
#include "SphareTest.h"

void EnemyGenerator::Start()
{
}

void EnemyGenerator::Update()
{
	if (m_isMove == true)
	{
		m_moveForce = m_moveSpeed;

		GetOwner()->m_transform->m_position.x += m_moveForce * GetOwner()->m_transform->GetAxisZ().x;
		GetOwner()->m_transform->m_position.z += m_moveForce * GetOwner()->m_transform->GetAxisZ().y;

		if (m_timer >= m_moveTime)
		{
			m_timer = 0.0f;
			m_isMove = false;
		}
	}
	else
	{
		// 回転
		GetOwner()->m_transform->m_rotation.y += m_rotSpeed * Timer::DeltaTime();

		// 弾発射
		if (m_timer >= m_fireInterval)
		{
			auto sphere = GameObjectManager::GetInstance()->Instance<SphareTest>("Sphare(clone)");

			m_timer = 0.0f;
			m_fireCounter++;
			if (m_fireCounter >= 10)
			{
				m_fireCounter = 0;
				m_isMove = true;
				m_timer = 0.0f;
			}
		}
	}

	// デルタタイム取得
	m_timer += Timer::DeltaTime();
}

void EnemyGenerator::End()
{
}
