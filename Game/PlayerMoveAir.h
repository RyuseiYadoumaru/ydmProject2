#pragma once
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
	bool m_canAirMove = false;
	
	// 無重力パラメータ
	MY_MATH::Vector3 m_startPosition;
	MY_MATH::Vector3 m_endPosition;

	uInt32 m_counter = 0;
};

