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
	// �J�����擾
	m_activeCamera = GameObjectManager::GetInstance()->Find("Camera")->GetComponent<PlayerActionCamera>();
	if (m_activeCamera != nullptr)
	{

		GetOwner()->m_transform->m_Rotation.y = (m_activeCamera->GetHorizontalAngle() + 0.0f);
	}

	// �A�j���[�^�[�擾
	m_animator = GetOwner()->GetComponent<Animator>();

	// �X�e�[�g�}�V��������
	m_stateMachine.Register("MoveGround", std::make_shared<PlayerMoveGround>(this));
	m_stateMachine.Register("MoveAir", std::make_shared<PlayerMoveAir>(this));
	m_stateMachine.Register("Fall", std::make_shared<PlayerFallState>(this));
	m_stateMachine.Register("LandGround", std::make_shared<PlayerLandGround>(this));
	m_stateMachine.Register("IdleAir", std::make_shared<PlayerAirIdle>(this));
	m_stateMachine.ChangeState("MoveGround");

	// �I���W�i�����W�n�擾
	m_originTransform = GetOwner()->GetComponent<PlayerOriginTransform>();
	
	// �A�C�e���擾 
	m_hitObjectManager = GameObjectManager::GetInstance()->Find("HitObjectManager");
	m_itemManger = m_hitObjectManager->GetComponent<ItemManager>();
	TOOLS::Debug::Assert(m_itemManger == nullptr);

	// �����蔻��擾
	m_sphereCollider = GetOwner()->GetComponent<SphereCollider>();
	TOOLS::Debug::Assert(m_sphereCollider == nullptr);
}

void PlayerMovement::Update()
{
	// �ړ��ʏ�����
	m_moveForce.Set(0.0f, 0.0f, 0.0f);

	// �X�e�[�g�}�V���X�V
	m_stateMachine.Update();

	// �q�b�g�A�C�e�����폜
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

	// �ړ�
	//m_originTransform->m_Position += m_moveForce;
	GetOwner()->m_transform->m_Position += m_moveForce;
}

void PlayerMovement::End()
{
	m_stateMachine.End();
}
