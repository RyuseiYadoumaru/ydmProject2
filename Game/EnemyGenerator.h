#pragma once
#include "GameContents.h"
USING_GAME_SYSTEMS;

class SphareTest;

class EnemyGenerator : public Script
{
private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	// ’e”­ŽË
	uInt32 m_fireCounter = 0;
	Float32 m_fireInterval = 0.3f;
	Float32 m_timer = 0.0f;

	// ‰ñ“]
	Float32 m_rotForce = 0.0f;
	Float32 m_rotSpeed = 50.0f;

	// ˆÚ“®
	bool m_isMove = false;
	Float32 m_moveTime = 2.0f;
	Float32 m_moveForce = 0.0f;
	Float32 m_moveSpeed = 7.5f;
};
