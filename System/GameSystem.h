//*****************************************************************************
//* @file   GameSystem.h
//* @brief  �Q�[���V�X�e���N���X
//* @note   �Q�[���V�X�e���ɕK�v�ȃV�X�e�����Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "Core/SubSystem.h"
#include "std.h"
#include "macro.h"

namespace gameSystems
{
	class Subsystem;
	class GameSubSystem;
	class GameSystemManager;
}

namespace gameUpdate
{
	enum class Type
	{
		/**
		* �V�X�e���X�V.
		*/
		System	= 0,
		
		/**
		* ���C���X�V.
		*/
		Main	= 1,
		
		/**
		 * �Ō�ɍs���X�V.
		 */
		Last	= 2,

		/**
		 * �X�V�Ȃ�.
		 */
		None,
	};
}

namespace systems
{
	class GameSystem : public SubSystem
	{
		SINGLETON_CLASS(GameSystem);

	public:
		bool SetUp()	override;
		bool ShutDown() override;
		bool Run();
		bool GameSystemStart();
		bool GameSystemEnd();

	};
}
