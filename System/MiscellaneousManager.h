//*****************************************************************************
//* @file   MiscellaneousManager.h
//* @brief  
//* @note   システムコンポーネントの更新を管理する
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "Miscellaneous.h"

namespace GAME_SYSTEMS
{
	class MiscellaneousManager
	{
		SINGLETON_CLASS(MiscellaneousManager);

	public:
		bool FirstUpdate()
		{
			for (auto& miscellaneousStage : m_destroyList)
			{
				for (auto& miscellaneous : miscellaneousStage.second)
				{
					miscellaneous->End();
					miscellaneous = nullptr;
				}
			}
			m_destroyList.clear();

			for (auto& miscellaneousStage : m_instanceList)
			{
				for (auto& miscellaneous : miscellaneousStage.second)
				{
					miscellaneous->Start();
					m_miscellaneousList[miscellaneous->m_type][miscellaneous->m_id] = miscellaneous;
					miscellaneous = nullptr;
				}
			}
			m_instanceList.clear();
			return true;
		}

		bool Update()
		{
			for (auto& miscellaneousStage : m_miscellaneousList)
			{
				for (auto& miscellaneous : miscellaneousStage.second)
				{
					miscellaneous.second->Update();
				}
			}
			return true;
		}

		bool Releace()
		{
			for (auto& miscellaneousStage : m_destroyList)
			{
				for (auto& miscellaneous : miscellaneousStage.second)
				{
					miscellaneous->End();
					miscellaneous = nullptr;
				}
			}
			for (auto& miscellaneousStage : m_miscellaneousList)
			{
				for (auto& miscellaneous : miscellaneousStage.second)
				{
					miscellaneous.second->End();
					miscellaneous.second = nullptr;
				}
			}
			m_miscellaneousList.clear();
			m_instanceList.clear();
			m_destroyList.clear();
			return true;
		}

	public:
		void Register(Miscellaneous* miscellaneous)
		{
			m_instanceList[miscellaneous->m_type].emplace_back(miscellaneous);
		}

		void Remove(Miscellaneous* miscellaneous)
		{
			m_destroyList[miscellaneous->m_type].emplace_back(miscellaneous);
			m_miscellaneousList[miscellaneous->m_type].erase(miscellaneous->m_id);
		}

	private:
		Map<Miscellaneous::Type, Vector<Miscellaneous*>> m_instanceList;
		Map<Miscellaneous::Type, Vector<Miscellaneous*>> m_destroyList;
		Map<Miscellaneous::Type, Unordered_Map<uInt32, Miscellaneous*>> m_miscellaneousList;

	};
}
