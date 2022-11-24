#pragma once
#include "GameContents.h"
USING_GAME_SYSTEMS;

class MoveMentSphere : public Script
{
private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	Float32 m_speed = 10.0f;
	Float32 m_moveForce = 0.0f;

	Float32 m_survivalTime = 5.0f;
	Float32 m_timer = 0.0f;

private:
	GameObjectPtr m_generator = nullptr;
};
