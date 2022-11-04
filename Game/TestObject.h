#pragma once

#include "GameObject.h"
class TestObject : public gameSystems::GameObject
{
public:
	GAMEOBJECT_CLASS;

public:
	virtual void Setting() override;

};
