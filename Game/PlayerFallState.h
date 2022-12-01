#pragma once
#include "PlayerActionState.h"

class PlayerFallState : public PlayerActionState
{
public:
	PLAYER_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

};
