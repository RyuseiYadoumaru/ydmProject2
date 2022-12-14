#pragma once
#include "CameraActionState.h"

class CameraGround : public CameraActionState
{
public:
	CAMERA_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

};
