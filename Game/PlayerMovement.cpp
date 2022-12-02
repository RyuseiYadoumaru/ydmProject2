#include "PlayerMovement.h"
#include "PlayerActionCamera.h"

#include "PlayerMoveGround.h"
#include "PlayerMoveAir.h"
#include "PlayerFallState.h"
#include "PlayerLandGround.h"

void PlayerMovement::Start()
{
	// �J�����擾
	m_activeCamera = GameObjectManager::GetInstance()->Find("Camera")->GetComponent<PlayerActionCamera>();
	if (m_activeCamera != nullptr)
	{

		GetOwner()->m_transform->m_rotation.y = (m_activeCamera->GetHorizontalAngle() + 0.0f);
	}

	// �A�j���[�^�[�擾
	m_animator = GetOwner()->GetComponent<Animator>();

	// �X�e�[�g�}�V��������
	m_stateMachine.Register("MoveGround", std::make_shared<PlayerMoveGround>(this));
	m_stateMachine.Register("MoveAir", std::make_shared<PlayerMoveAir>(this));
	m_stateMachine.Register("Fall", std::make_shared<PlayerFallState>(this));
	m_stateMachine.Register("LandGround", std::make_shared<PlayerLandGround>(this));
	m_stateMachine.ChangeState("MoveGround");

}

void PlayerMovement::Update()
{
	// �ړ��ʏ�����
	m_moveForce.Set(0.0f, 0.0f, 0.0f);

	// �X�e�[�g�}�V���X�V
	m_stateMachine.Update();

	// �ړ�
	GetOwner()->m_transform->m_position += m_moveForce;
}

void PlayerMovement::End()
{
	m_stateMachine.End();
}
