//******************************************************************************
//* @file   GameSubSystemInstance.h
//* @brief  �Q�[���T�u�V�X�e���C���X�^���X
//* @note   �S�ẴQ�[���T�u�V�X�e���̐����A�Q�Ƃ��s��
//* @note	�Q�[���̃T�u�V�X�e���̐����͏d�v�Ȗ����̒S���̂ŁA��{�I�ɂ����̏������Ő�������
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "GameSubSysmte.h"
#include "Debug.h"


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
		gameSubSystem.IsRegistered();
	};

	class GameSubSystemInstance
	{
		SINGLETON_CLASS(GameSubSystemInstance);
		using GameSubSystemList = Unordered_Map <String, SharedPtr<GameSubSystem>>;

	public:
		/**============================================================================
		//! @func   Create
		//! @brief  �Q�[���T�u�V�X�e���𐶐�
		============================================================================*/
		template<TGameSubSystem TYPE>
		SharedPtr<TYPE> Create(String name, bool isSingleton = true)
		{
			// �V���O���g���̏ꍇ�����f�[�^�^���Ȃ����T������
			for (auto& subsystem : m_gameSubSystems)
			{
				SharedPtr<TYPE> check = std::dynamic_pointer_cast<TYPE>(subsystem.second);
				if (check != nullptr)
				{
					if (check->IsSingleton() == true || isSingleton == true)
					{
						tools::Debug::LogWarning("�V���O���g���̈א����ł��܂���>>>>>>>", check->GetName());
						return nullptr;
					}
					break;
				}
			}
			
			// �������O�̃V�X�e���͐������Ȃ�
			if(m_gameSubSystems[name] != nullptr)
			{
				tools::Debug::LogError("�Q�[���T�u�V�X�e���̖��O���d�����Ă��܂�>>>>>>>", name);
				tools::Debug::Log("�d�����Ȃ����O�ŃQ�[���T�u�V�X�e����ݒ肵�Ă�������");
				return nullptr;
			}
			auto buff = std::make_shared<TYPE>(name, isSingleton);
			m_gameSubSystems.insert(std::make_pair(name, buff));
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
			if (m_gameSubSystems.count(systemName) == 0)
			{
				tools::Debug::LogError("�Q�[���V�X�e���̎Q�ƂɎ��s���܂���>>>>>>", systemName);
				return nullptr;
			}

			if (m_gameSubSystems[systemName]->IsRegistered() == false)
			{
				tools::Debug::LogError("�Q�[���V�X�e���̓V�X�e���ɓo�^����Ă��܂���");
				return nullptr;
			}

			auto buff = std::dynamic_pointer_cast<TYPE>(m_gameSubSystems[systemName]);
			return buff;
		}

		/**============================================================================
		//! @func   Releace
		//! @brief  �Q�[���T�u�V�X�e���������
		============================================================================*/
		void Releace() noexcept
		{
			for (auto& system : m_gameSubSystems)
			{
				system.second->Finalize();
			}
			m_gameSubSystems.clear();
		}

	private:
		GameSubSystemList m_gameSubSystems;
	};
}





