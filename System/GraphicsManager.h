//*****************************************************************************
//* @file   GraphicsManager.h
//* @brief  
//* @note   グラフィックコンポーネントの更新を管理する
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "Graphics.h"

namespace GAME_SYSTEMS
{
	class GraphicsManager
	{
		SINGLETON_CLASS(GraphicsManager);

	public:
		bool StartUpdate()
		{
			for (auto& graphicsStage : m_instanceList)
			{
				for (auto& graphics : graphicsStage.second)
				{
					graphics->Start();
					m_graphicsList[graphics->m_type][graphics->m_id] = graphics;
					graphics = nullptr;
				}
			}
			m_instanceList.clear();
			return true;
		}

		bool DestroyUpdate()
		{
			for (auto& graphicsStage : m_destroyList)
			{
				for (auto& graphics : graphicsStage.second)
				{
					graphics->End();
					graphics = nullptr;
				}
			}
			m_destroyList.clear();
			return true;
		}

		bool Update()
		{
			for (auto& graphicsStage : m_graphicsList)
			{
				for (auto& graphics : graphicsStage.second)
				{
					graphics.second->Update();
				}
			}
			return true;
		}

		bool Releace()
		{
			for (auto& graphicsStage : m_destroyList)
			{
				for (auto& graphics : graphicsStage.second)
				{
					graphics->End();
					graphics = nullptr;
				}
			}
			for (auto& graphicsStage : m_graphicsList)
			{
				for (auto& graphics : graphicsStage.second)
				{
					graphics.second->End();
					graphics.second = nullptr;
				}
			}
			m_graphicsList.clear();
			m_instanceList.clear();
			m_destroyList.clear();
			return true;
		}

	public:
		void Register(Graphics* graphics)
		{
			m_instanceList[graphics->m_type].emplace_back(graphics);
		}

		void Remove(Graphics* graphics)
		{
			m_destroyList[graphics->m_type].emplace_back(graphics);
			m_graphicsList[graphics->m_type].erase(graphics->m_id);
		}

	private:
		Map<Graphics::Type, Vector<Graphics*>> m_instanceList;
		Map<Graphics::Type, Vector<Graphics*>> m_destroyList;
		Map<Graphics::Type, Unordered_Map<uInt32, Graphics*>> m_graphicsList;

	};
}
