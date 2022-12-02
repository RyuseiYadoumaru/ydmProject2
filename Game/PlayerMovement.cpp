#include "PlayerMovement.h"
#include "PlayerActionCamera.h"

#include "PlayerMoveGround.h"
#include "PlayerMoveAir.h"
#include "PlayerFallState.h"
#include "PlayerLandGround.h"

void PlayerMovement::Start()
{
	// カメラ取得
	m_activeCamera = GameObjectManager::GetInstance()->Find("Camera")->GetComponent<PlayerActionCamera>();
	if (m_activeCamera != nullptr)
	{

		GetOwner()->m_transform->m_rotation.y = (m_activeCamera->GetHorizontalAngle() + 0.0f);
	}

	// アニメーター取得
	m_animator = GetOwner()->GetComponent<Animator>();

	// ステートマシン初期化
	m_stateMachine.Register("MoveGround", std::make_shared<PlayerMoveGround>(this));
	m_stateMachine.Register("MoveAir", std::make_shared<PlayerMoveAir>(this));
	m_stateMachine.Register("Fall", std::make_shared<PlayerFallState>(this));
	m_stateMachine.Register("LandGround", std::make_shared<PlayerLandGround>(this));
	m_stateMachine.ChangeState("MoveGround");

}

void PlayerMovement::Update()
{
	// 移動量初期化
	m_moveForce.Set(0.0f, 0.0f, 0.0f);

	// ステートマシン更新
	m_stateMachine.Update();

	// 移動
	GetOwner()->m_transform->m_position += m_moveForce;
}

void PlayerMovement::End()
{
	m_stateMachine.End();
}
