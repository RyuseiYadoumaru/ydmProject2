//*****************************************************************************
//* @file   GameObjectManager.h
//* @brief  
//* @note   全てのオブジェクトを管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "GameObject.h"


namespace GAME_SYSTEMS
{
	class World;
	class GameObject;
	using GameObjectPtr = SharedPtr<GameObject>;

	template<class T>
	concept TGameObject = requires(GameObject& object)
	{
		object.GetTag();
	};


	class GameObjectManager
	{
		SINGLETON_CLASS(GameObjectManager);

	public:

		// ゲームオブジェクト生成
		template<TGameObject TYPE>
		SharedPtr<TYPE> Instance(String name)
		{
			SharedPtr<TYPE> instance = std::make_shared<TYPE>(name);
			instance->Setting();
			m_instanceObjectList.push_back(instance);
			return instance;

		}
		// ゲームオブジェクト削除
		void Destroy(GameObjectPtr gameObject);

	private:
		bool GameObjectSetUp();
		bool GameObjectStartUpdate();
		bool GameLogicUpdate();
		bool ComponentUpdate();
		bool GameObjectShutDown();

	private:
		Unordered_Map<uInt32, GameObjectPtr> m_gameObjectList;
		Vector<GameObjectPtr> m_instanceObjectList;
		Vector<GameObjectPtr> m_destroyObjectList;

	private:
		friend World;
	};
}
