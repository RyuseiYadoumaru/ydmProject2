#pragma once
#include "GameContents.h"

class PlayerActionCamera;

#define CAMERA_ACTION_STATE using CameraActionState::CameraActionState;

class CameraActionState : public GAME_SYSTEMS::StateBase
{
public:
	CameraActionState(PlayerActionCamera* owner) : m_owner(owner) {}
	~CameraActionState() = default;

protected:
	PlayerActionCamera* m_owner;
};
