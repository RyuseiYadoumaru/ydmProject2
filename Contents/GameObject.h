//*****************************************************************************
//* @file   GameObject.h
//* @brief  ゲームオブジェクトクラス
//* @note   ゲームで使用するオブジェクトクラス
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include "GameObjectHeader.h"

#define GAMEOBJECT_CLASS using gameSystems::GameObject::GameObject;

namespace GAME_SYSTEMS
{
	class GameObject : public systems::Object
	{
	public:
		const Tag& GetTag() const noexcept { return m_tag; }
		const uInt32& GetID() const noexcept{ return m_id; }

	public:		
		/**
		 * ゲームオブジェクトが所持しているコンポーネントを取得します.
		 * Templateで型を指定します。所持してないものの場合はnullptrを返す
		 * 
		 * !@return Component
		 */
		template<TComponent T>
		TComponentPtr<T> GetComponent()
		{
			for (auto& comp : m_componentList)
			{
				auto component = std::dynamic_pointer_cast<T>(comp);
				if (component != nullptr) return component;
			}
			return nullptr;
		}

		/**
		 * コンポーネントを追加します.
		 * 失敗した場合はnullptrを返します
		 * 
		 * !@return Component
		 */
		template <TComponent T>
		TComponentPtr<T> AddComponent(bool active = true)
		{
			TComponentPtr<T> component = std::make_shared<T>();
			component->SetOwner(this);
			component->SetActive(active);
			component->Initialize();
			m_componentList.push_back(component);
			return component;
		}


	protected:
		Tag m_tag;

	private:
		ComponentContainer m_componentList;
		ScriptContainer m_scriptList;

	private:
		virtual void Setting() = 0;
		void ShutDown();

		void ComponentStart();
		void ComponentEnd();

	public:
		GameObject(String name = "nonameObject") :
			systems::Object(name, true),
			m_tag(Tag::Default) {}
		~GameObject() = default;

		friend GameObjectManager;
	};
}

