#include "ThirdPersonCamera.h"
USING_TOOLS;

void ThirdPersonCamera::FocusObject()
{
	// ���S���W�擾
	Float32 centerPositionX = m_focusTransform->GetPosition().x;
	Float32 centerPositionZ = m_focusTransform->GetPosition().z;

	Vector4 zaxis = m_focusTransform->GetAxisZ();

	// �x���@���ʓx�@�ɕϊ�����
	Float32 horizontalRadian = (m_horizontalAngle + 90.0f) * 3.14f / 180.0f;
	Float32 verticalRadian = m_verticalAngle * 3.14f / 180.0f;

	// �t�H�[�J�[�X�I�u�W�F�N�g�̒��S���W����̉~��̈ʒu
	Float32 addPositionX = cos(horizontalRadian) * m_horizontalRadius;
	Float32 addPositionY = sin(verticalRadian) * m_verticalRadius;
	Float32 addPositionZ = sin(horizontalRadian) * m_horizontalRadius;
	m_camera->m_eye.Set(
		m_focusTransform->GetPosition().x + addPositionX,
		m_focusTransform->GetPosition().y + addPositionY + m_heightOffset,
		m_focusTransform->GetPosition().z + addPositionZ
	);

	// �����_���t�H�[�J�X�I�u�W�F�N�g�Ɍ�����
	m_camera->m_lookAt.Set(
		m_focusTransform->GetPosition().x,
		m_focusTransform->GetPosition().y,
		m_focusTransform->GetPosition().z
	);
	m_camera->m_lookAt += m_lookAtOffset;

	// �J�����̏�x�N�g�����t�H�[�J�X�I�u�W�F�N�g�ɓ���
	//m_camera->m_up.Set(
	//	m_focusTransform->GetAxisY().x,
	//	m_focusTransform->GetAxisY().y,
	//	m_focusTransform->GetAxisY().z
	//);

}

void ThirdPersonCamera::Start()
{
	m_focusObject = GameObjectManager::GetInstance()->Find("Player");
	Debug::Assert(m_focusObject == nullptr);
	m_focusTransform = m_focusObject->GetComponent<Transform>();
	Debug::Assert(m_focusTransform == nullptr);
	m_camera = GetOwner()->GetComponent<Camera>();
	Debug::Assert(m_camera == nullptr);

	m_lookAtOffset.Set( 0.0f, 30.0f, 0.0f );

	FocusObject();
}

void ThirdPersonCamera::Update()
{
	FocusObject();

	Vector2 moveForce = { 0.0f, 0.0f };
	
	moveForce.x = m_movevSensitivity * GamePad::RightStick().x;
	moveForce.y = m_movevSensitivity * GamePad::RightStick().y;

	m_horizontalAngle += moveForce.x;
	m_verticalAngle += moveForce.y;

	if (m_verticalAngle > m_limitVerticalAngle) m_verticalAngle = m_limitVerticalAngle;
	if (m_verticalAngle < -m_limitVerticalAngle) m_verticalAngle = -m_limitVerticalAngle;


}

void ThirdPersonCamera::End()
{
}
