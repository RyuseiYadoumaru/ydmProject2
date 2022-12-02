#pragma once
#include "GameContents.h"

class PlayerTrackingCamera : public GAME_SYSTEMS::DefaultCamera
{
public:
	CAMERA_CLASS;

private:
	virtual void Setting() override;
};