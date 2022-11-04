//******************************************************************************
//* @file   GameSubSystemManager.h
//* @brief  �Q�[���T�u�V�X�e���}�l�[�W���[
//* @note   �S�ẴQ�[���T�u�V�X�e���̐����A�Q�Ƃ��s��
//* @note	�Q�[���̃T�u�V�X�e���̐����͏d�v�Ȗ����̒S���̂ŁA��{�I�ɂ����̏������Ő�������
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "Debug.h"
#include "GameSubSysmte.h"
#include "GameSystem.h"


namespace gameSystems
{
	template<class T>
	concept TGameSubSystem = requires(T gameSubSystem)
	{
		gameSubSystem.Initialize();
		gameSubSystem.Run();
		gameSubSystem.Finalize();
		gameSubSystem.GetName();
		gameSubSystem.IsSingleton();
	};

	class GameSystemManager
	{
		SINGLETON_CLASS(GameSystemManager);

		friend systems::GameSystem;

		using GameSubSystemPtr = SharedPtr<gameSystems::GameSubSystem>;
		 // �T�u�V�X�e�����Ǘ�����R���e�i->[�D��x][�V�X�e����][�Q�[���T�u�V�X�e��]
		using SubsystemContainer = Map<uInt64, Unordered_Map<String, GameSubSystemPtr>>;
		// �V�X�e���̃X�e�[�W->�X�V�X�e�[�W��
		using SystemStage = Map<gameUpdate::Type, SubsystemContainer>;

	public:
		/**============================================================================
		//! @func   Create
		//! @brief  �Q�[���T�u�V�X�e���𐶐�
		============================================================================*/
		template<TGameSubSystem TYPE>
		SharedPtr<TYPE> Create(String name, gameUpdate::Type type, uInt32 priority = 128, bool isSingleton = true)
		{
			// �V���O���g���̏ꍇ�����f�[�^�^���Ȃ����T������
			for (auto& stage : m_gameSubSystemList)
			{
				for (auto& subSystemList : stage.second)
				{
					if (subSystemList.second.contains(name) == true)
					{
						// ���O���d������ꍇ�D��x���Ⴄ�ꍇ�ł����O����
						tools::Debug::LogError("�Q�[���T�u�V�X�e���̖��O���d�����Ă��܂��F", name);
						return nullptr;
					}

					for (auto& subSystem : subSystemList.second)
					{
						auto check = std::dynamic_pointer_cast<TYPE>(subSystem.second);
						if (check != nullptr)
						{
							if (check->IsSingleton() == true || isSingleton == true)
							{
								tools::Debug::LogWarning("�V���O���g���̈א����ł��܂���F", check->GetName());
								return nullptr;
							}
						}
					}
				}
			}
			auto buff = std::make_shared<TYPE>(name, priority, type, isSingleton);
			m_gameSubSystemList[type][priority][name] = buff;
			return buff;
		}

		/**============================================================================
		//! @func   GetSubSystem
		//! @brief  �T�u�V�X�e���擾
		//! @note	�Q�[���V�X�e���ɓo�^����Ă�����̂��Q�Ƃ���
		============================================================================*/
		template<TGameSubSystem TYPE>
		SharedPtr<TYPE> GetSubSystem(String systemName)
		{
			for (auto& stage : m_gameSubSystemList)
			{
				for (auto& subSystemList : stage.second)
				{
					if (subSystemList.second.contains(systemName) == true)
					{
						auto buff = std::dynamic_pointer_cast<TYPE>(subSystemList.second.at(systemName));
						return buff;
					}
				}
			}
			return nullptr;
		}

	public:
		void Releace();

	private:
		SystemStage m_gameSubSystemList;
	};
}





