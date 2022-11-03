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

namespace GAME_SYSTEMS
{
	class GameObject;
	class Component : public systems::Object
	{
	public:
		OBJECT_CLASS;
		Component() : SYSTEMS::Object("Component", true) {}
		~Component() = default;

		virtual void Update() {}

	public:
		bool Run() { if (m_isActive == true) Update(); return true; }
		void SetOwner(GameObject* gameObject) noexcept { m_owner = gameObject; }
		GameObject* GetOwner()  noexcept { return m_owner; }

	public:
	
	private:
		GameObject* m_owner = nullptr;
	};


}