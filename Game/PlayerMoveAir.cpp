#include "GameContents.h"
#include "PlayerMoveAir.h"
#include "PlayerMovement.h"
#include "PlayerActionCamera.h"

void PlayerMoveAir::EnterState()
{
	m_canAirMove = false;
	// ���������ݒ�
	m_startPosition = m_owner->GetOwner()->m_transform->m_position;
	m_endPosition.x = m_startPosition.x;
	m_endPosition.y = m_startPosition.y + m_owner->GetAirHeight();
	m_endPosition.z = m_startPosition.z;

	m_counter = 0;

	// �󒆈ړ��v���C
	m_owner->GetAnimator()->Play("AirMove");
}

void PlayerMoveAir::ExitState()
{
}

void PlayerMoveAir::Update()
{
	auto transform = m_owner->GetOwner()->m_transform;

	if (m_canAirMove == true)
	{
		// �ړ�����
		//AirMoveMent();

		if (GamePad::LeftTrigger() >= GamePad::m_XinputTriggerMax)
		{
			// �n�ʈړ��ɐ؂�ւ�
			m_owner->GetStateMachine().ChangeState("Fall");
			return;
		}
	}

	// �����Ă���i�K
	else
	{
		// ����
		uInt32 time = m_owner->GetAirFrameCount();
		auto larpParam = Easing::SineOut(static_cast<Float32>(m_counter), static_cast<Float32>(time), 0.0f, 1.0f);
		if (m_counter >= time)
		{
			larpParam = 1.0f;
			m_canAirMove = true;
			m_counter = 0;
		}

		// �㏸
		transform->m_position = Vector3::Larp(m_startPosition, m_endPosition, larpParam);
	}

	// �g�[�^���^�C�����Z
	m_counter++;
}

void PlayerMoveAir::AirMoveMent()
{
	// �e�I�u�W�F�N�g���W
	auto transform = m_owner->GetOwner()->m_transform;

	// �ړ��ʃp�����[�^
	Float32 moveForwardForce = 0.0f;
	Float32 angle = 0.0f;
	Float32 movePower = 0.0f;

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
		transform->m_rotation.y = (camera->GetHorizontalAngle() + angle);
		if (transform->m_rotation.y > 360.0f)
		{
			transform->m_rotation.y -= 360.0f;
		}

		// �ړ��ʌ���
		moveForwardForce = m_owner->GetMoveSpeed() * fabsf(movePower);
	}
	else
	{
		m_isResetCamera = false;
	}

	// �ړ�
	m_owner->SetMoveForce(
		moveForwardForce * transform->GetAxisY().x * -1.0f,
		moveForwardForce * transform->GetAxisY().y * -1.0f,
		moveForwardForce * transform->GetAxisY().z * -1.0f);
}
