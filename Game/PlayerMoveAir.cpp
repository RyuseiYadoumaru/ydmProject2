#include "GameContents.h"
#include "PlayerMoveAir.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"
#include "PlayerActionCamera.h"

USING_GAME_SYSTEMS;
USING_MY_MATH;

void PlayerMoveAir::EnterState()
{
	// �J�����R���|�[�l���g�擾
	m_camera = m_owner->GetActiveCamera()->GetOwner()->GetComponent<Camera>();

	m_isRotation = true;

	auto transform = m_owner->GetOwner()->m_transform;
	auto playerCamera = m_owner->GetActiveCamera();
	m_owner->GetOriginTransform()->SetType(PlayerOriginTransform::Type::ZeroGravity);
	
	// ��]�J�n�ʒu
	m_startAxis = transform->m_Rotation;

	// ��]�I���ʒu
	auto mtx = transform->GetWorldMatrix();
	Quaternion qt = Quaternion::CreateByMartix(mtx);

	// �E����]�x�N�g��
	Vector3 upAxis;
	upAxis = transform->GetAxisZ();
	Vector3 cross = Vector3::Cross(m_camera->GetAxisZ(), upAxis);
	Vector4 rightAxis;
	rightAxis = cross;
	Quaternion qtX = Quaternion::CreateByRotationAxis(rightAxis, -60.0f);
	Quaternion rightQt = Quaternion::Multiply(qt, qtX);

	// �㎲��]�x�N�g��
	auto cameraAngle = playerCamera->GetHorizontalAngle();
	if (cameraAngle > 360.0f)
	{
		cameraAngle -= 360.0f;
	}
	Vector4 playerUp;
	playerUp = upAxis;
	
	// �J�������I�C���[�p�Ńv���C���[�̎������]���Ă��邽��
	// �I�C���[�p�̃v���C���[�p�x���擾����
	Float32 verticalAngle = 0.0f;
	verticalAngle = m_owner->GetOriginTransform()->m_Rotation.y - cameraAngle;
	Quaternion qtY = Quaternion::CreateByRotationAxis(playerUp, verticalAngle);
	m_endAxis = Quaternion::Multiply(rightQt, qtY);
	//m_endAxis = Quaternion::Multiply(qt ,qtY);

	// �J�����̌����Ă�������ɐi��
	m_moveVector = m_camera->GetAxisZ();

	m_counter = 0;
	m_rotCounter = 0;
}

void PlayerMoveAir::ExitState()
{
	m_saveEuler = m_owner->GetOriginTransform()->GetSaveRotation();
}

void PlayerMoveAir::Update()
{
	//auto transform = m_owner->GetOriginTransform();
	auto transform = m_owner->GetOwner()->m_transform;
	AirMoveMent();
	
	if (m_isRotation == true)
	{
		Float32 slerp = Easing::Liner(static_cast<Float32>(m_counter), static_cast<Float32>(m_owner->GetAirRotationCount()), 0.001f, 1.0f);
		if (m_rotCounter >= m_owner->GetAirRotationCount())
		{
			slerp = 1.0f;
			m_isRotation = false;
			m_rotCounter = 0;
		}
		auto slerpQt = Quaternion::Slerp(m_startAxis, m_endAxis, slerp);
		//transform->m_QtRotation = slerpQt;
		transform->m_Rotation = slerpQt;
		m_rotCounter++;
	}

	// ������x���͂����Ƃ��Ɏ~�܂�
	if (GamePad::RightTrigger() >= GamePad::m_XinputTriggerMax &&
		GamePad::OldRightTrigger() != GamePad::m_XinputTriggerMax)
	{
		m_owner->GetStateMachine().ChangeState("IdleAir");
		return;
	}
	m_counter++;
}

void PlayerMoveAir::AirMoveMent()
{
	// �e�I�u�W�F�N�g���W
	auto transform = m_owner->GetOwner()->m_transform;
		
	// �ړ��ʃp�����[�^
	Float32 moveForwardForce = 0.0f;
	Float32 angle = 0.0f;
	Float32 movePower = 1.0f;

	// �ړ��ʌ���
	Float32 max = static_cast<Float32>(m_owner->GetAirMaxSpeedFrame());
	Float32 speed = Easing::ExpoOut(static_cast<Float32>(m_counter), max, 0.5f, 1.0f);
	moveForwardForce = m_owner->GetAirMaxSpeed() * speed;

	// �ړ�
	m_owner->SetMoveForce(
		moveForwardForce * m_moveVector.x,
		moveForwardForce * m_moveVector.y,
		moveForwardForce * m_moveVector.z);
}
