//*****************************************************************************
//* @file   World.h
//* @brief  
//* @note   �Q�[���̃V�[����I�u�W�F�N�g�̏�����,�X�V���Ǘ�����
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

