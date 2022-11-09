//*****************************************************************************
//* @file   ThirdPersonCamera.h
//* @brief  
//* @note   三人称視点のカメラ
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "GameContents.h"
USING_GAME_SYSTEMS;
USING_MY_MATH;

class ThirdPersonCamera : public Script
{
private:
	constexpr static  Float32 m_limitVerticalAngle = 90.0f;

private:
	GameObjectPtr m_focusObject;
	SharedPtr<Transform> m_focusTransform;
	SharedPtr<Camera> m_camera;

	Vector3 m_lookAtOffset;
	Float32 m_heightOffset = 200.0f;
	Float32 m_horizontalRadius = 300.0f;
	Float32 m_verticalRadius = 100.0f;
	Float32 m_horizontalAngle = 0.0f;
	Float32 m_verticalAngle = 0.0f;

	Float32 m_movevSensitivity = 10.0f;


private:
	void FocusObject();


private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;
};
