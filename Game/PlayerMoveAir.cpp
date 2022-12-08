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

	m_owner->GetOriginTransform()->SetType(PlayerOriginTransform::Type::ZeroGravity);
	m_isRotation = true;

	m_startAxis = m_owner->GetOriginTransform()->m_QtRotation;

	//auto transPos = m_owner->GetOriginTransform()->m_Position;
	//Vector3 forwardVec = m_camera->m_eye - transPos;
	//m_endAxis.x = forwardVec.x;
	//m_endAxis.y = forwardVec.y;
	//m_endAxis.z = forwardVec.z;
	//m_endAxis.w = 0.0f;
	m_counter = 0;
	m_rotCounter = 0;

	m_moveVector = m_camera->GetAxisZ();
	m_endAxis = m_moveVector * -1.0f;
	m_endAxis.Normalize();

}

void PlayerMoveAir::ExitState()
{
}

void PlayerMoveAir::Update()
{
	//auto transform = m_owner->GetOwner()->m_transform;
	auto transform = m_owner->GetOriginTransform();
	AirMoveMent();
	
	if (m_isRotation == true)
	{
		TOOLS::Debug::DrawAxis(transform->m_Position, m_endAxis.GetVector4(), 500.0f, Color::Yellow);
		Float32 slerp = Easing::Liner(m_counter, m_owner->GetAirRotationCount(), 0.001f, 1.0f);
		if (m_rotCounter >= m_owner->GetAirRotationCount())
		{
			slerp = 1.0f;
			m_isRotation = false;
			m_rotCounter = 0;
		}
		auto slerpQt = Quaternion::Slerp(m_startAxis, m_endAxis, slerp);
		transform->m_QtRotation = slerpQt;
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
	moveForwardForce = m_owner->GetMoveSpeed() * fabsf(movePower);

	// 移動
	auto cameraForwardVec = m_camera->GetAxisZ();
	m_owner->SetMoveForce(
		moveForwardForce * m_moveVector.x,
		moveForwardForce * m_moveVector.y,
		moveForwardForce * m_moveVector.z);
}
