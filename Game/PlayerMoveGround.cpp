#include "PlayerMoveGround.h"
#include "PlayerMovement.h"
#include "PlayerActionCamera.h"
#include "GameContents.h"

void PlayerMoveGround::EnterState()
{
	m_isResetCamera = false;
}

void PlayerMoveGround::ExitState()
{
}

void PlayerMoveGround::Update()
{
	// �e�I�u�W�F�N�g���W
	auto transform = m_owner->GetOwner()->m_transform;

	// �ړ��ʃp�����[�^
	Float32 moveForwardForce = 0.0f;
	Float32 angle = 0.0f;
	Float32 movePower = 0.0f;

	// ��]
	auto rotation = transform->GetEulerAngles();

	// �ړ�
	if (GamePad::LeftStick().x != 0.0f || GamePad::LeftStick().y != 0.0f)
	{
		// ���͏���
		Float32 h = GamePad::LeftStick().x;
		Float32 v = GamePad::LeftStick().y;

		// �ړ���
		movePower = sqrtf(powf(v, 2.0f) + powf(h, 2.0f));
		if (movePower > 1.0f) movePower = 1.0f;
		auto camera = m_owner->GetActiveCamera();
		// �ړ�����
		if (camera->IsReset() == true)
		{
			m_isResetCamera = true;
		}
		if (m_isResetCamera == false)
		{
			Float32 rad = atanf(h / v);
			angle = rad * 360.0f / DirectX::XM_2PI;
			// �p�x��90�x�ȏ�ŕ��̒l�ɂȂ邽��
			// �␳��360�x�ɂȂ�悤�ɏC������
			if (v < 0 && h < 0) angle += 180.0f;
			else if (v < 0) angle = (180.0f + angle);
			else if (h < 0) angle = (360.0f + angle);
		}

		// �p�x����
		rotation.y = (camera->GetHorizontalAngle() + angle);
		if (rotation.y > 360.0f)
		{
			rotation.y -= 360.0f;
		}

		// �ړ��ʌ���
		moveForwardForce = m_owner->GetMoveSpeed() * fabsf(movePower);
	}
	else
	{
		m_isResetCamera = false;
	}

	// �󒆃��[�h
	if (GamePad::RightTrigger() >= GamePad::m_XinputTriggerMax &&
		GamePad::OldRightTrigger() != GamePad::m_XinputTriggerMax)
	{
		m_owner->GetStateMachine().ChangeState("MoveAir");
		return;
	}

	// �A�j���[�V����
	auto blend = Easing::SineOut(moveForwardForce, m_owner->GetMoveSpeed(), 0.0f, 1.0f);
	m_owner->GetAnimator()->Play("MoveMent", blend);

	// �ړ�
	m_owner->SetMoveForce(
	moveForwardForce * transform->GetAxisY().x * -1.0f,
	moveForwardForce * transform->GetAxisY().y * -1.0f,
	moveForwardForce * transform->GetAxisY().z * -1.0f);

	// ��]
	//transform->SetRotation(rotation.x, rotation.y, rotation.z);
}
