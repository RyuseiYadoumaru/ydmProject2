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
	class PhysicsManager;
	class Physics : public systems::Component
	{
	public:
		enum class Type
		{
			Transform,
			SphereCollider
		};

		explicit Physics(String name, Type type) :
			systems::Component(name, true),
			m_type(type) {}
		~Physics() = default;

	public:
		void Initialize() override;
		void Finalize() override;

	private:
		Type m_type;

	private:
		friend PhysicsManager;

	};
}
