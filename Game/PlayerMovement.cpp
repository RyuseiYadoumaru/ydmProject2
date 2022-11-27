#include "PlayerMovement.h"
#include "ThirdPersonCamera.h"

void PlayerMovement::Start()
{
	m_activeCamera = GameObjectManager::GetInstance()->Find("Camera")->GetComponent<ThirdPersonCamera>();
	if (m_activeCamera != nullptr)
	{

		GetOwner()->m_transform->m_rotation.y = (m_activeCamera->GetHorizontalAngle() + 0.0f);
	}

	m_renderer = GetOwner()->GetComponent<SkinnedMeshRenderer>();
	//m_animator = GetOwner()->GetComponent<Animator>();

}

void PlayerMovement::Update()
{
	// 前移動
	// UnrealEngineからExportしたモデルなのでZupになっている
	auto trans = GetOwner()->m_transform;
	GetOwner()->m_transform->m_position.x += -m_moveForce.z * trans->GetAxisY().x;
	GetOwner()->m_transform->m_position.y += -m_moveForce.z * trans->GetAxisY().y;
	GetOwner()->m_transform->m_position.z += -m_moveForce.z * trans->GetAxisY().z;

	Float32 angle = 0.0f;
	Float32 movePower = 0.0f;
	m_moveForce.Set( 0.0f, 0.0f ,0.0f );
	if (GamePad::LeftStick().x != 0.0f || GamePad::LeftStick().y != 0.0f)
	{
		// 入力処理
		Float32 h = GamePad::LeftStick().x;
		Float32 v = GamePad::LeftStick().y;
		
		// 移動量
		movePower = sqrtf(powf(v, 2.0f) + powf(h, 2.0f));
		if (movePower > 1.0f) movePower = 1.0f;
		
		// 移動方向
		if (m_activeCamera->IsReset() == true)
		{
			m_resetCamera = true;
		}
		if (m_resetCamera == false)
		{
			Float32 rad = atanf(h / v);
			angle = rad * 360.0f / DirectX::XM_2PI;
			// 角度が90度以上で負の値になるため
			// 補正の360度になるように修正する
			if (v < 0 && h < 0) angle += 180.0f;
			else if (v < 0) angle = (180.0f + angle);
			else if( h < 0) angle = (360.0f + angle);
		}

		// 角度決定
		GetOwner()->m_transform->m_rotation.y = (m_activeCamera->GetHorizontalAngle() + angle);
		if (GetOwner()->m_transform->m_rotation.y > 360.0f) GetOwner()->m_transform->m_rotation.y -= 360.0f;
		m_moveForce.z = m_moveSpeed * fabsf(movePower);
	}
	else
	{
		m_resetCamera = false;
	}

	// アニメーション
	auto blend = Easing::SineOut(m_moveForce.z, m_moveSpeed, 0.0f, 1.0f);
	//m_animator->Play("MoveMent", blend);
}

void PlayerMovement::End()
{
}
