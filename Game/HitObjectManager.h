#pragma once
#include "GameContents.h"

class HitObjectManager : public GAME_SYSTEMS::GameObject
{
	GAMEOBJECT_CLASS;

private:
	void Setting() override;
};
