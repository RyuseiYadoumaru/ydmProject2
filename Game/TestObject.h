#pragma once

#include "GameObject.h"
#include "ModelData.h"

class TestObject : public gameSystems::GameObject
{
public:
	GAMEOBJECT_CLASS;

public:
	virtual void Setting() override;
	SharedPtr<GAME_SYSTEMS::ModelData> m_modelData;

};
