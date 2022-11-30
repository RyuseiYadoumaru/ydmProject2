#pragma once
#include "GameContents.h"

class PlayerMovement;

#define PLAYER_ACTION_STATE using PlayerActionState::PlayerActionState;

class PlayerActionState : public GAME_SYSTEMS::StateBase
{
public:
	PlayerActionState(PlayerMovement* owner): m_owner(owner) {}
	~PlayerActionState() = default;

protected:
	PlayerMovement* m_owner;

};
