//*****************************************************************************
//* @file   Component.h
//* @brief  コンポーネントクラス
//* @note   すべてのコンポーネントの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once

#include "../System/Core/Object.h"
#include "std.h"
#include "macro.h"

#define COMPONENT_CLASS using systems::Component::Component;

namespace GAME_SYSTEMS
{
	class GameObject;
}

namespace SYSTEMS
{
	class Component : public Object
	{
	public:
		OBJECT_CLASS;

	public:
		virtual void Initialize() {};
		virtual void Finalize() {};

	public:
		void SetOwner(gameSystems::GameObject* gameObject) noexcept { m_owner = gameObject; }
		gameSystems::GameObject* GetOwner()  noexcept { return m_owner; }

	protected:
		virtual void Start()	= 0;
		virtual void Update()	= 0;
		virtual void End()		= 0;

	private:
		friend gameSystems::GameObject;
		gameSystems::GameObject* m_owner = nullptr;
	};


}