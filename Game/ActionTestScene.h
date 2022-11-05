#pragma once
#include "Scene.h"

class ActionTestScene : public gameSystems::Scene
{
	SCENE_CLASS;
public:
	virtual void ObjectEntry() override;
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void EndPlay() override;
	virtual void Render() override;

};