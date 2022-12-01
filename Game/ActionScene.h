#pragma once
#include "SceneHelper.h"

class ActionScene : public GAME_SYSTEMS::Scene
{
	SCENE_CLASS;

private:
	virtual void ObjectEntry() override;
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void EndPlay() override;

private:
	GameObjectPtr m_player = nullptr;
	uInt32 m_frameCounter = 0;

};
