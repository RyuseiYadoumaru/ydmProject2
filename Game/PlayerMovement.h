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

class PlayerActionCamera;

class PlayerMovement : public Script
{
public:
	// カメラ
	SharedPtr<PlayerActionCamera> GetActiveCamera() const noexcept { return m_activeCamera; }

	// アニメーション
	SharedPtr<Animator> GetAnimator() const noexcept { return m_animator; }

	// ステートマシン
	GAME_SYSTEMS::StateMachine& GetStateMachine() noexcept { return m_stateMachine; }

	// 移動
	const Float32& GetMoveSpeed() const noexcept { return m_moveSpeed; }
	void SetMoveForce(Float32 forceX, Float32 forceY, Float32 forceZ) noexcept { m_moveForce.Set(forceX, forceY, forceZ); }
	const Vector3& GetMoveForce() const noexcept { return m_moveForce; }

	// 空中移動
	const Float32& GetAirHeight() const noexcept { return m_airHeight; }
	const uInt32& GetAirFrameCount() const noexcept { return m_airFrameCount; }

	// 着地
	const Float32& GetGravity() const noexcept { return m_gravity; }
	const Float32& GetMaxFallSpeed() const noexcept { return m_fallMaxSpeed; }
	const uInt32& GetMaxFallSpeedFrame() const noexcept { return m_maxFallSpeedFrame; }
	const uInt32& GetLandStopFrame() const noexcept { return m_landStopFrame; }

private:
	// ステートマシン
	GAME_SYSTEMS::StateMachine m_stateMachine;

	// 移動パラメータ
	Float32 m_moveSpeed = 10.0f;
	Vector3 m_moveForce;

	// 空中移動
	Float32 m_airHeight = 300.0f;
	uInt32 m_airFrameCount = 20;

	// 着地
	Float32 m_gravity = 9.8f;
	Float32 m_fallMaxSpeed = 15.0f;
	uInt32 m_maxFallSpeedFrame = 20;
	uInt32 m_landStopFrame = 10;

	// カメラ
	SharedPtr<PlayerActionCamera> m_activeCamera = nullptr;

	// アニメーション
	SharedPtr<Animator> m_animator = nullptr;

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

};
