//*****************************************************************************
//* @file   PhysicsManager.h
//* @brief  
//* @note   物理系コンポーネントの更新を管理する
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "Physics.h"

namespace GAME_SYSTEMS
{
	class PhysicsManager
	{
		SINGLETON_CLASS(PhysicsManager);

	public:
		bool StartUpdate()
		{

			for (auto& physicsStage : m_instanceList)
			{
				for (auto& physics : physicsStage.second)
				{
					physics->Start();
					m_physicsList[physics->m_type][physics->m_id] = physics;
					physics = nullptr;
				}
			}
			m_instanceList.clear();
			return true;
		}

		bool DestroyUpdate()
		{
			for (auto& physicsStage : m_destroyList)
			{
				for (auto& physics : physicsStage.second)
				{
					physics->End();
					physics = nullptr;
				}
			}
			m_destroyList.clear();
			return true;
		}

		bool Update()
		{
			for (auto& physicsStage : m_physicsList)
			{
				for (auto& physics : physicsStage.second)
				{
					physics.second->Update();
				}
			}
			return true;
		}

		bool Releace()
		{
			for (auto& physicsStage : m_destroyList)
			{
				for (auto& physics : physicsStage.second)
				{
					physics->End();
					physics = nullptr;
				}
			}
			for (auto& physicsStage : m_physicsList)
			{
				for (auto& physics : physicsStage.second)
				{
					physics.second->End();
					physics.second = nullptr;
				}
			}
			m_physicsList.clear();
			m_instanceList.clear();
			m_destroyList.clear();
			return true;
		}

	public:
		void Register(Physics* physics)
		{
			m_instanceList[physics->m_type].emplace_back(physics);
		}

		void Remove(Physics* physics)
		{
			m_destroyList[physics->m_type].emplace_back(physics);
			m_physicsList[physics->m_type].erase(physics->m_id);
		}

	private:
		Map<Physics::Type, Vector<Physics*>> m_instanceList;
		Map<Physics::Type, Vector<Physics*>> m_destroyList;
		Map<Physics::Type, Unordered_Map<uInt32, Physics*>> m_physicsList;

	};
}
