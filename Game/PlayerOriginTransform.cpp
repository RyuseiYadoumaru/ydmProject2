#include "PlayerOriginTransform.h"

void PlayerOriginTransform::Start()
{
	m_transform = GetOwner()->GetComponent<Transform>();
	m_Position = m_transform->m_Position;
}

void PlayerOriginTransform::Update()
{
	m_transform->m_Position = m_Position;
	// 地面の時と無重力の時で回転のさせ方を変える
	if (m_type == Type::Ground)
	{
		m_transform->m_Rotation = Quaternion::CreateByRotation(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		m_QtRotation = m_transform->m_Rotation;
	}
	if (m_type == Type::ZeroGravity)
	{
		m_transform->m_Rotation = m_QtRotation;
		m_Rotation = Quaternion::EulerAngles(m_QtRotation);
	}

	printf("\n\nX:%fY:%fZ:%f", m_Rotation.x, m_Rotation.y, m_Rotation.z);
}

void PlayerOriginTransform::End()
{
}
