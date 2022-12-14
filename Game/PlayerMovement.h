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
class PlayerOriginTransform;
class Item;
class HitObjectManager;
class ItemManager;

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
	const uInt32& GetAirRotationCount() const noexcept { return m_airRotationCount; }
	const uInt32& GetAirIdleResetFrame() const noexcept { return m_airIdleResetFrame; }
	const uInt32& GetAirMaxSpeedFrame() const noexcept { return m_airMaxSpeedFrame; }
	const Float32& GetAirMaxSpeed() const noexcept { return m_airMaxSpeed; }

	// 着地
	const Float32& GetGravity() const noexcept { return m_gravity; }
	const Float32& GetMaxFallSpeed() const noexcept { return m_fallMaxSpeed; }
	const uInt32& GetMaxFallSpeedFrame() const noexcept { return m_maxFallSpeedFrame; }
	const uInt32& GetLandStopFrame() const noexcept { return m_landStopFrame; }

	// アイテム取得
	const Int32& GetItemHitStopFrame() const noexcept { return m_itemHitStopFrame; }
	bool IsHitStop() const noexcept { return m_isHitStop; }
	void SetIsHitStop(bool flag) noexcept { m_isHitStop = flag; }

	// 姿勢
	const Vector4& GetForwardAxis() const noexcept { return m_forwardAxis; }
	void SetForwardAxis(const Vector4& forwardAxis) noexcept { m_forwardAxis = forwardAxis; }

	// オリジナル座標系
	SharedPtr<PlayerOriginTransform> GetOriginTransform() noexcept { return m_originTransform; }

private:
	// ステートマシン
	GAME_SYSTEMS::StateMachine m_stateMachine;

	// 移動パラメータ
	Float32 m_moveSpeed = 10.0f;
	Vector3 m_moveForce;

	// 空中移動
	Float32 m_airHeight = 300.0f;
	uInt32 m_airFrameCount = 20;
	uInt32 m_airRotationCount = 70;
	uInt32 m_airIdleResetFrame = 60;
	Float32 m_airMaxSpeed = 30.0f;
	uInt32 m_airMaxSpeedFrame = 5;

	// 着地
	Float32 m_gravity = 9.8f;
	Float32 m_fallMaxSpeed = 17.0f;
	uInt32 m_maxFallSpeedFrame = 15;
	uInt32 m_landStopFrame = 10;


	// カメラ
	SharedPtr<PlayerActionCamera> m_activeCamera = nullptr;

	// アニメーション
	SharedPtr<Animator> m_animator = nullptr;

	// アイテム
	GameObjectPtr m_item = nullptr;
	GameObjectPtr m_hitObjectManager = nullptr;
	SharedPtr<ItemManager> m_itemManger = nullptr;
	Int32 m_hitStopCounter = 0;
	Int32 m_itemHitStopFrame = 4;
	bool m_isHitStop = false;

	// 姿勢
	Vector4 m_forwardAxis;

	// オリジナル座標系
	SharedPtr<PlayerOriginTransform> m_originTransform = nullptr;

	SharedPtr<SphereCollider> m_sphereCollider = nullptr;


private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

};
