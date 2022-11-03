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

namespace GAME_SYSTEMS
{
	class GameObject : public systems::Object
	{
	public:
		const Tag& GetTag() const noexcept { return m_tag; }

	public:
		GameObject(String name, Tag tag = Tag::Default) :
			m_tag(tag),
			SYSTEMS::Object(name, true) {}

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

	public:
		bool Initialize() override { InstanceProcess(); return true; }
		bool Run() override { Process(); return true; }
		bool Finalize() override { DestroyProcess(); return true; }

	protected:
		virtual void OnEnable()		= 0;
		virtual void Start()		= 0;

		virtual void Update()		= 0;
		virtual void FixedUpdate()	= 0;

		virtual void End()			= 0;
		virtual void OnDisable()	= 0;


	protected:
		void InstanceProcess() noexcept;

		void Process() noexcept;

		void DestroyProcess() noexcept;

	private:
		ComponentContainer m_componentList;
		Tag m_tag;

	};
}

