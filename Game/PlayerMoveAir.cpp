#include "GameContents.h"
#include "PlayerMoveAir.h"
#include "PlayerMovement.h"
#include "PlayerActionCamera.h"

USING_GAME_SYSTEMS;

void PlayerMoveAir::EnterState()
{
	m_canAirMove = false;
	m_isAirMove = false;
	// 浮く高さ設定
	m_startPosition = m_owner->GetOwner()->m_transform->m_position;
	m_endPosition.x = m_startPosition.x;
	m_endPosition.y = m_startPosition.y + m_owner->GetAirHeight();
	m_endPosition.z = m_startPosition.z;

	m_counter = 0;

	// 空中移動プレイ
	m_owner->GetAnimator()->Play("AirMove");

	// カメラコンポーネント取得
	m_camera = m_owner->GetActiveCamera()->GetOwner()->GetComponent<Camera>();
}

void PlayerMoveAir::ExitState()
{
}

void PlayerMoveAir::Update()
{
	auto transform = m_owner->GetOwner()->m_transform;

	if (m_canAirMove == true)
	{
		// 　入力処理
		if (GamePad::LeftTrigger() >= GamePad::m_XinputTriggerMax &&
			GamePad::OldLeftTrigger() != GamePad::m_XinputTriggerMax)
		{
			// 地面移動に切り替え
			m_owner->GetStateMachine().ChangeState("Fall");
			return;
		}
		else if (GamePad::RightTrigger() >= GamePad::m_XinputTriggerMax &&
				GamePad::OldRightTrigger() != GamePad::m_XinputTriggerMax)
		{
			m_isAirMove = !m_isAirMove;
		}


		// 移動処理
		if (m_isAirMove == true)
		{
			AirMoveMent();
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
	Float32 movePower = 1.0f;

	// 移動量決定
	moveForwardForce = m_owner->GetMoveSpeed() * fabsf(movePower);

	// 移動
	auto cameraForwardVec = m_camera->GetAxisZ();
	m_owner->SetMoveForce(
		moveForwardForce * cameraForwardVec.x * 1.0f,
		moveForwardForce * cameraForwardVec.y * 1.0f,
		moveForwardForce * cameraForwardVec.z * 1.0f);
}
