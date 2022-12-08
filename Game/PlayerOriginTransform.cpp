#include "PlayerOriginTransform.h"

void PlayerOriginTransform::Start()
{
	m_transform = GetOwner()->GetComponent<Transform>();
	m_Position = m_transform->m_Position;
}

void PlayerOriginTransform::Update()
{
	m_transform->m_Position = m_Position;
	// ’n–Ê‚ÌŽž‚Æ–³d—Í‚ÌŽž‚Å‰ñ“]‚Ì‚³‚¹•û‚ð•Ï‚¦‚é
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
