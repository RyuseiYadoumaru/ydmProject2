#pragma once
#include "GameContents.h"

USING_GAME_SYSTEMS;

class DebugCamera : public DefaultCamera
{
public:
	CAMERA_CLASS;

private:
	virtual void Setting() override;
};
