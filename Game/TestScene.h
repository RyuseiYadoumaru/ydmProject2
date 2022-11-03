//*****************************************************************************
//* @file   TestScene.h
//* @brief  
//* @note   テストシーン
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "Scene.h"

class TestScene : public gameSystems::Scene
{
public:
	SCENE_CLASS;

public:
	virtual void ObjectEntry() override;
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void EndPlay() override;
};
