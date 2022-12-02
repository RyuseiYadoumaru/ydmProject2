#pragma once
#include "PlayerActionState.h"

class PlayerLandGround : public PlayerActionState
{
public:
	PLAYER_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

private:
	uInt32 m_counter = 0;

};
