#pragma once
#include "PlayerActionState.h"

class PlayerMovement;

class PlayerMoveGround : public PlayerActionState
{
public:
	PLAYER_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

private:
	bool m_isResetCamera = false;

};