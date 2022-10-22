//*****************************************************************************
//* @file   GameSystem.h
//* @brief  �Q�[���V�X�e���N���X
//* @note   �Q�[���V�X�e���ɕK�v�ȃV�X�e�����Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "SubSystem.h"
#include "std.h"
#include "macro.h"

namespace gameSystems
{
	class Subsystem;
	class GameSubSystem;
	class Manager;
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

		/**
		 * GameSubsystem�̃|�C���^.
		 */
		using GameSubSystemPtr = SharedPtr<gameSystems::GameSubSystem>;

		/**
		 * �V�X�e���X�e�[�W.
		 */
		// �T�u�V�X�e�����Ǘ�����R���e�i->[�D��x][�V�X�e����][�Q�[���T�u�V�X�e��]
		using SubsystemContainer	= Map<uInt64, Unordered_Map<String, GameSubSystemPtr>>;
		// �V�X�e���̃X�e�[�W->�X�V�X�e�[�W��
		using SystemStage			= Map<gameUpdate::Type, SubsystemContainer>;

	public:
		bool SetUp()	override;
		bool ShutDown() override;
		bool Run();
		bool Initialaze();
		bool Finalize();

	private:
		void AddSubSystem(GameSubSystemPtr set);

	private:
		SystemStage m_stageList;
		friend gameSystems::GameSubSystem;

	};
}
