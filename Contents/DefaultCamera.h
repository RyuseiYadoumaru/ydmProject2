//*****************************************************************************
//* @file   DefaultCamera.h
//* @brief  デフォルトカメラクラス
//* @note   ゲームで使用する標準的なカメラ
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "GameObject.h"

namespace GAME_SYSTEMS
{
	class DefaultCamera : public GameObject
	{
	public:
		GAMEOBJECT_CLASS;

	private:
		virtual void SetUp() override;
		virtual void Setting() override;
		friend GameObjectManager;

	};
}