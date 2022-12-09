#include "GameContents.h"
#include "PlayerMoveAir.h"
#include "PlayerMovement.h"
#include "PlayerOriginTransform.h"
#include "PlayerActionCamera.h"

USING_GAME_SYSTEMS;
USING_MY_MATH;

void PlayerMoveAir::EnterState()
{
	// カメラコンポーネント取得
	m_camera = m_owner->GetActiveCamera()->GetOwner()->GetComponent<Camera>();

	m_isRotation = true;

	auto transform = m_owner->GetOwner()->m_transform;
	auto playerCamera = m_owner->GetActiveCamera();
	m_owner->GetOriginTransform()->SetType(PlayerOriginTransform::Type::ZeroGravity);
	
	// 回転開始位置
	m_startAxis = transform->m_Rotation;

	// 回転終了位置
	auto mtx = transform->GetWorldMatrix();
	Quaternion qt = Quaternion::CreateByMartix(mtx);

	// 右軸回転ベクトル
	Vector3 upAxis;
	upAxis = transform->GetAxisZ();
	Vector3 cross = Vector3::Cross(m_camera->GetAxisZ(), upAxis);
	Vector4 rightAxis;
	rightAxis = cross;
	Quaternion qtX = Quaternion::CreateByRotationAxis(rightAxis, -60.0f);
	Quaternion rightQt = Quaternion::Multiply(qt, qtX);

	// 上軸回転ベクトル
	auto cameraAngle = playerCamera->GetHorizontalAngle();
	if (cameraAngle > 360.0f)
	{
		cameraAngle -= 360.0f;
	}
	Vector4 playerUp;
	playerUp = upAxis;
	
	// カメラをオイラー角でプレイヤーの周りを回転しているため
	// オイラー角のプレイヤー角度を取得する
	Float32 verticalAngle = 0.0f;
	verticalAngle = m_owner->GetOriginTransform()->m_Rotation.y - cameraAngle;
	Quaternion qtY = Quaternion::CreateByRotationAxis(playerUp, verticalAngle);
	m_endAxis = Quaternion::Multiply(rightQt, qtY);
	//m_endAxis = Quaternion::Multiply(qt ,qtY);

	// カメラの向いている方向に進む
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

	// もう一度入力したときに止まる
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
	// 親オブジェクト座標
	auto transform = m_owner->GetOwner()->m_transform;
		
	// 移動量パラメータ
	Float32 moveForwardForce = 0.0f;
	Float32 angle = 0.0f;
	Float32 movePower = 1.0f;

	// 移動量決定
	Float32 max = static_cast<Float32>(m_owner->GetAirMaxSpeedFrame());
	Float32 speed = Easing::ExpoOut(static_cast<Float32>(m_counter), max, 0.5f, 1.0f);
	moveForwardForce = m_owner->GetAirMaxSpeed() * speed;

	// 移動
	m_owner->SetMoveForce(
		moveForwardForce * m_moveVector.x,
		moveForwardForce * m_moveVector.y,
		moveForwardForce * m_moveVector.z);
}
