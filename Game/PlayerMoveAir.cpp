#include "GameContents.h"
#include "PlayerMoveAir.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"
#include "PlayerActionCamera.h"

USING_GAME_SYSTEMS;

void PlayerMoveAir::EnterState()
{
	// �J�����R���|�[�l���g�擾
	m_camera = m_owner->GetActiveCamera()->GetOwner()->GetComponent<Camera>();

	m_owner->GetOriginTransform()->SetType(PlayerOriginTransform::Type::ZeroGravity);
}

void PlayerMoveAir::ExitState()
{
}

void PlayerMoveAir::Update()
{
	//auto transform = m_owner->GetOwner()->m_transform;
	auto transform = m_owner->GetOriginTransform();
	AirMoveMent();
	
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
	moveForwardForce = m_owner->GetMoveSpeed() * fabsf(movePower);

	// �ړ�
	auto cameraForwardVec = m_camera->GetAxisZ();
	m_owner->SetMoveForce(
		moveForwardForce * cameraForwardVec.x * 1.0f,
		moveForwardForce * cameraForwardVec.y * 1.0f,
		moveForwardForce * cameraForwardVec.z * 1.0f);
}
