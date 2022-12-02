#include "GameContents.h"
#include "PlayerMoveAir.h"
#include "PlayerMovement.h"
#include "PlayerActionCamera.h"

void PlayerMoveAir::EnterState()
{
	m_canAirMove = false;
	// 浮く高さ設定
	m_startPosition = m_owner->GetOwner()->m_transform->m_position;
	m_endPosition.x = m_startPosition.x;
	m_endPosition.y = m_startPosition.y + m_owner->GetAirHeight();
	m_endPosition.z = m_startPosition.z;

	m_counter = 0;

	// 空中移動プレイ
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
		// 移動処理
		//AirMoveMent();

		if (GamePad::LeftTrigger() >= GamePad::m_XinputTriggerMax)
		{
			// 地面移動に切り替え
			m_owner->GetStateMachine().ChangeState("Fall");
			return;
		}
	}

	// 浮いている段階
	else
	{
		// 浮く
		uInt32 time = m_owner->GetAirFrameCount();
		auto larpParam = Easing::SineOut(static_cast<Float32>(m_counter), static_cast<Float32>(time), 0.0f, 1.0f);
		if (m_counter >= time)
		{
			larpParam = 1.0f;
			m_canAirMove = true;
			m_counter = 0;
		}

		// 上昇
		transform->m_position = Vector3::Larp(m_startPosition, m_endPosition, larpParam);
	}

	// トータルタイム加算
	m_counter++;
}

void PlayerMoveAir::AirMoveMent()
{
	// 親オブジェクト座標
	auto transform = m_owner->GetOwner()->m_transform;

	// 移動量パラメータ
	Float32 moveForwardForce = 0.0f;
	Float32 angle = 0.0f;
	Float32 movePower = 0.0f;

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
		transform->m_rotation.y = (camera->GetHorizontalAngle() + angle);
		if (transform->m_rotation.y > 360.0f)
		{
			transform->m_rotation.y -= 360.0f;
		}

		// 移動量決定
		moveForwardForce = m_owner->GetMoveSpeed() * fabsf(movePower);
	}
	else
	{
		m_isResetCamera = false;
	}

	// 移動
	m_owner->SetMoveForce(
		moveForwardForce * transform->GetAxisY().x * -1.0f,
		moveForwardForce * transform->GetAxisY().y * -1.0f,
		moveForwardForce * transform->GetAxisY().z * -1.0f);
}
