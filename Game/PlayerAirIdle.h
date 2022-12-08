#pragma once
#include "GameContents.h"
#include "PlayerActionState.h"

class PlayerAirIdle : public PlayerActionState
{
public:
	PLAYER_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

private:
	// ���d�̓p�����[�^
	MY_MATH::Vector3 m_startPosition;
	MY_MATH::Vector3 m_endPosition;

	uInt32 m_counter = 0;

	bool m_isRiseUp = false;

};

