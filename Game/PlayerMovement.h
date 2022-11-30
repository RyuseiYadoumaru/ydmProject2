//*****************************************************************************
//* @file   PlayerMovement.h
//* @brief  
//* @note   プレイヤーの動き
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "GameContents.h"
USING_GAME_SYSTEMS;
USING_MY_MATH;

class ThirdPersonCamera;

class PlayerMovement : public Script
{
public:
	// カメラ
	SharedPtr<ThirdPersonCamera> GetActiveCamera() const noexcept { return m_activeCamera; }

	// アニメーション
	SharedPtr<Animator> GetAnimator() const noexcept { return m_animator; }

	// 移動
	const Float32& GetMoveSpeed() const noexcept { return m_moveSpeed; }
	void SetMoveForce(Float32 forceX, Float32 forceY, Float32 forceZ) noexcept { m_moveForce.Set(forceX, forceY, forceZ); }
	const Vector3& GetMoveForce() const noexcept { return m_moveForce; }

private:
	// ステートマシン
	GAME_SYSTEMS::StateMachine m_stateMachine;

	// 移動パラメータ
	Float32 m_moveSpeed = 10.0f;
	Vector3 m_moveForce;

	// カメラ
	SharedPtr<ThirdPersonCamera> m_activeCamera = nullptr;

	// アニメーション
	SharedPtr<Animator> m_animator = nullptr;

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

};
