#pragma once
#include "GameContents.h"
USING_GAME_SYSTEMS;

class DebugCameraMovement : public Script
{
public:
	void SetDebugCamera(GameObject* camera) noexcept { m_debugCamera = camera; }
private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	GameObject* m_debugCamera = nullptr;
	SharedPtr<GAME_SYSTEMS::Camera> m_camera = nullptr;

	Float32 m_speed = 10.0f;
};
