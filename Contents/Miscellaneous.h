//*****************************************************************************
//* @file   Miscellaneous.h
//* @brief  
//* @note   雑多なコンポーネントの基底クラス
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

	class Miscellaneous : public systems::Component
	{
	public:
		enum class Type
		{
			Animator
		};

		Miscellaneous(String name, Type type) :
			systems::Component(name, true),
			m_type(type) {}
		~Miscellaneous() = default;

	private:
		static bool MiscellaneousUpdate();
		static bool MiscellaneousReleace();

	private:
		static Map<Type, Unordered_Map<uInt32, Miscellaneous*>> m_miscellaneousList;

	public:
		void Initialize() override;
		void Finalize() override;


	private:
		Type m_type;
	private:
		friend GameObjectManager;
	};
}
