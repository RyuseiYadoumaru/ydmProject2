#include "PlayerMovement.h"
#include "PlayerActionCamera.h"
#include "PlayerOriginTransform.h"

#include "PlayerMoveGround.h"
#include "PlayerMoveAir.h"
#include "PlayerFallState.h"
#include "PlayerLandGround.h"
#include "PlayerAirIdle.h"

#include "Item.h"
#include "ItemManager.h"

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
	
	// アイテム取得 
	m_hitObjectManager = GameObjectManager::GetInstance()->Find("HitObjectManager");
	m_itemManger = m_hitObjectManager->GetComponent<ItemManager>();
	TOOLS::Debug::Assert(m_itemManger == nullptr);

	// 当たり判定取得
	m_sphereCollider = GetOwner()->GetComponent<SphereCollider>();
	TOOLS::Debug::Assert(m_sphereCollider == nullptr);
}

void PlayerMovement::Update()
{
	// 移動量初期化
	m_moveForce.Set(0.0f, 0.0f, 0.0f);

	// ステートマシン更新
	m_stateMachine.Update();

	// ヒットアイテムを削除
	auto itemList = m_itemManger->GetItemList();
	uInt32 index = 0;
	for (auto& item : itemList)
	{
		if (item != nullptr)
		{
			auto col = item->GetComponent<SphereCollider>();
			if (m_sphereCollider->HitCheck(col) == true)
			{
				GameObjectManager::GetInstance()->Destroy(item);
				m_itemManger->DeleteItem(index);
				m_isHitStop = true;
			}
		}
		index++;
	}

	// 移動
	//m_originTransform->m_Position += m_moveForce;
	GetOwner()->m_transform->m_Position += m_moveForce;
}

void PlayerMovement::End()
{
	m_stateMachine.End();
}
