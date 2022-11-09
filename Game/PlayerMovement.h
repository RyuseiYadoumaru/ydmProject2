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

class PlayerMovement : public Script
{
private:
	Vector3 m_moveForce;
	Float32 m_moveSpeed = 10.0f;

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

};
