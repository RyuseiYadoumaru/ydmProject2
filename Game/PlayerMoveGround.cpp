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
	// 親オブジェクト座標
	auto transform = m_owner->GetOwner()->m_transform;

	// 移動量パラメータ
	Float32 moveForwardForce = 0.0f;
	Float32 angle = 0.0f;
	Float32 movePower = 0.0f;

	// 回転
	auto rotation = transform->GetEulerAngles();

	// 移動
	if (GamePad::LeftStick().x != 0.0f || GamePad::LeftStick().y != 0.0f)
	{
		// 入力処理
		Float32 h = GamePad::LeftStick().x;
		Float32 v = GamePad::LeftStick().y;

		// 移動量
		movePower = sqrtf(powf(v, 2.0f) + powf(h, 2.0f));
		if (movePower > 1.0f) movePower = 1.0f;
		auto camera = m_owner->GetActiveCamera();
		// 移動方向
		if (camera->IsReset() == true)
		{
			m_isResetCamera = true;
		}
		if (m_isResetCamera == false)
		{
			Float32 rad = atanf(h / v);
			angle = rad * 360.0f / DirectX::XM_2PI;
			// 角度が90度以上で負の値になるため
			// 補正の360度になるように修正する
			if (v < 0 && h < 0) angle += 180.0f;
			else if (v < 0) angle = (180.0f + angle);
			else if (h < 0) angle = (360.0f + angle);
		}

		// 角度決定
		rotation.y = (camera->GetHorizontalAngle() + angle);
		if (rotation.y > 360.0f)
		{
			rotation.y -= 360.0f;
		}

		// 移動量決定
		moveForwardForce = m_owner->GetMoveSpeed() * fabsf(movePower);
	}
	else
	{
		m_isResetCamera = false;
	}

	// 空中モード
	if (GamePad::RightTrigger() >= GamePad::m_XinputTriggerMax &&
		GamePad::OldRightTrigger() != GamePad::m_XinputTriggerMax)
	{
		m_owner->GetStateMachine().ChangeState("MoveAir");
		return;
	}

	// アニメーション
	auto blend = Easing::SineOut(moveForwardForce, m_owner->GetMoveSpeed(), 0.0f, 1.0f);
	m_owner->GetAnimator()->Play("MoveMent", blend);

	// 移動
	m_owner->SetMoveForce(
	moveForwardForce * transform->GetAxisY().x * -1.0f,
	moveForwardForce * transform->GetAxisY().y * -1.0f,
	moveForwardForce * transform->GetAxisY().z * -1.0f);

	// 回転
	//transform->SetRotation(rotation.x, rotation.y, rotation.z);
}
