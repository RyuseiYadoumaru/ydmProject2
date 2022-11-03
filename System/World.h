//*****************************************************************************
//* @file   World.h
//* @brief  
//* @note   ゲームのシーンやオブジェクトの初期化,更新を管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "GameSubSysmte.h"


namespace GAME_SYSTEMS
{
	class World : public GameSubSystem
	{
		GAMESUBSYSTEM;

	public:
		bool Initialize() override;
		bool Run() override;
		bool Finalize() override;

	};
}

