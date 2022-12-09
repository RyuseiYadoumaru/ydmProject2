#include "PlayerOriginTransform.h"

void PlayerOriginTransform::SetType(Type type) noexcept
{
	m_type = type;
	
	if (m_isStart == true)
	{
		if (type == Type::Ground )
		{
			m_Rotation = m_saveRotation;
		}
		else if (type == Type::ZeroGravity)
		{
			m_QtRotation = m_transform->m_Rotation;
		}
	}

}
void PlayerOriginTransform::Start()
{
	m_transform = GetOwner()->GetComponent<Transform>();
	m_Position = m_transform->m_Position;
	m_transform->m_Rotation = Quaternion::CreateByRotation(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_saveRotation = m_Rotation;
	m_isStart = true;
}

void PlayerOriginTransform::Update()
{
	//m_transform->m_Position = m_Position;
	// ’n–Ê‚ÌŽž‚Æ–³d—Í‚ÌŽž‚Å‰ñ“]‚Ì‚³‚¹•û‚ð•Ï‚¦‚é
	if (m_type == Type::Ground)
	{
		m_transform->m_Rotation = Quaternion::CreateByRotation(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		m_QtRotation = m_transform->m_Rotation;
		m_saveRotation = m_Rotation;
	}
	//if (m_type == Type::ZeroGravity)
	//{
	//	m_transform->m_Rotation = m_QtRotation;
	//	m_Rotation = Quaternion::EulerAngles(m_QtRotation);
	//}
	//printf("\n\nX:%f,Y:%f,Z:%f,W:%f\n",
	//	m_transform->m_Rotation.x,
	//	m_transform->m_Rotation.y,
	//	m_transform->m_Rotation.z,
	//	m_transform->m_Rotation.w);
	//printf("\n\nX:%fY:%fZ:%f", m_Rotation.x, m_Rotation.y, m_Rotation.z);
}

void PlayerOriginTransform::End()
{
}
