#pragma once
#include "PlayerActionState.h"

class PlayerMovement;
class PlayerOriginTransform;

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
	bool m_isStart = false;

	PlayerOriginTransform* m_originTransform = nullptr;

};