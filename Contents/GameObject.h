//*****************************************************************************
//* @file   GameObject.h
//* @brief  �Q�[���I�u�W�F�N�g�N���X
//* @note   �Q�[���Ŏg�p����I�u�W�F�N�g�N���X
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
		SharedPtr<Transform> m_transform = nullptr;

	public:		
		/**
		 * �Q�[���I�u�W�F�N�g���������Ă���R���|�[�l���g���擾���܂�.
		 * Template�Ō^���w�肵�܂��B�������ĂȂ����̂̏ꍇ��nullptr��Ԃ�
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
		 * �R���|�[�l���g��ǉ����܂�.
		 * ���s�����ꍇ��nullptr��Ԃ��܂�
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

		/**
		 *  �R���|�[�l���g���폜���܂�.
		 * 
		 */
		//template<TComponent T>
		//void RemoveComponent()
		//{
		//	for (auto& comp : m_componentList)
		//	{
		//		auto component = std::dynamic_pointer_cast<T>(comp);
		//		if (component != nullptr)
		//		{
		//			component->Finalize();
		//			m_componentList.erase(component);
		//			return;
		//		}
		//	}
		//}

	protected:
		virtual void Setting() {};
		virtual void SetUp();
		virtual void ShutDown();

	protected:
		Tag m_tag;

	private:
		ComponentContainer m_componentList;

	public:
		GameObject(String name = "nonameObject") :
			systems::Object(name, true),
			m_tag(Tag::Default) {}
		GameObject(const GameObject&) = default;
		~GameObject() { m_componentList.clear(); }

		friend GameObjectManager;
	};
}

