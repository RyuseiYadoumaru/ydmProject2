#pragma once
#include "GameContents.h"
#include "PlayerActionState.h"


class PlayerMoveAir : public PlayerActionState
{
public:
	PLAYER_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

private:
	void AirMoveMent();

private:
	bool m_canAirMove = false;
	bool m_isAirMove = false;
	
	// 無重力パラメータ
	MY_MATH::Vector3 m_startPosition;
	MY_MATH::Vector3 m_endPosition;

	uInt32 m_counter = 0;

	bool m_isResetCamera = false;

	// カメラコンポーネント
	SharedPtr<GAME_SYSTEMS::Camera> m_camera = nullptr;
};

