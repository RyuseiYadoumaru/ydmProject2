//*****************************************************************************
//* @file   Physics.h
//* @brief  
//* @note   物理系のコンポーネントの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once

#include "macro.h"
#include "std.h"
#include "../System/Core/Component.h"


namespace GAME_SYSTEMS
{
	class GameObjectManager;

	class Physics : public systems::Component
	{
	public:
		enum class Type
		{
			Transform
		};

		Physics(String name, Type type) :
			systems::Component(name, true),
			m_type(type) {}
		~Physics() = default;

	private:
		static bool PhysicsUpdate();
		static bool PhysicsReleace();

	private:
		static Map<Type, Unordered_Map<uInt32, Physics*>> m_physicsList;;

	public:
		void Initialize() override;
		void Finalize() override;

	private:
		Type m_type;

	private:
		friend GameObjectManager;

	};
}
