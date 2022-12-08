#include "PlayerMovement.h"
#include "PlayerActionCamera.h"
#include "PlayerOriginTransform.h"

#include "PlayerMoveGround.h"
#include "PlayerMoveAir.h"
#include "PlayerFallState.h"
#include "PlayerLandGround.h"
#include "PlayerAirIdle.h"

void PlayerMovement::Start()
{
	// カメラ取得
	m_activeCamera = GameObjectManager::GetInstance()->Find("Camera")->GetComponent<PlayerActionCamera>();
	if (m_activeCamera != nullptr)
	{

		GetOwner()->m_transform->m_Rotation.y = (m_activeCamera->GetHorizontalAngle() + 0.0f);
	}

	// アニメーター取得
	m_animator = GetOwner()->GetComponent<Animator>();

	// ステートマシン初期化
	m_stateMachine.Register("MoveGround", std::make_shared<PlayerMoveGround>(this));
	m_stateMachine.Register("MoveAir", std::make_shared<PlayerMoveAir>(this));
	m_stateMachine.Register("Fall", std::make_shared<PlayerFallState>(this));
	m_stateMachine.Register("LandGround", std::make_shared<PlayerLandGround>(this));
	m_stateMachine.Register("IdleAir", std::make_shared<PlayerAirIdle>(this));
	m_stateMachine.ChangeState("MoveGround");

	// オリジナル座標系取得
	m_originTransform = GetOwner()->GetComponent<PlayerOriginTransform>();
}

void PlayerMovement::Update()
{
	// 移動量初期化
	m_moveForce.Set(0.0f, 0.0f, 0.0f);

	// ステートマシン更新
	m_stateMachine.Update();

	// 移動
	m_originTransform->m_Position += m_moveForce;
	//GetOwner()->m_transform->m_Position += m_moveForce;
}

void PlayerMovement::End()
{
	m_stateMachine.End();
}
