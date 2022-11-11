//*****************************************************************************
//* @file   PlayerMovement.h
//* @brief  
//* @note   ÉvÉåÉCÉÑÅ[ÇÃìÆÇ´
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "GameContents.h"
USING_GAME_SYSTEMS;
USING_MY_MATH;

class ThirdPersonCamera;

class PlayerMovement : public Script
{
	enum class State
	{
		Rotation,
		Movement
	};

private:
	Vector3 m_moveForce;
	Float32 m_moveSpeed = 10.0f;
	SharedPtr<SkinnedMeshRenderer> m_renderer = nullptr;
	SharedPtr<ThirdPersonCamera> m_activeCamera = nullptr;
	State m_state = State::Movement;

	bool m_resetCamera = false;


private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

};
