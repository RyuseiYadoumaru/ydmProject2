#pragma once
#include "GameContents.h"

class Item : public GAME_SYSTEMS::GameObject
{
	GAMEOBJECT_CLASS;
	
private:
	void Setting() override;
};
