//*****************************************************************************
//* @file   Graphics.h
//* @brief  
//* @note   グラフィック周りのコンポーネントの基底クラス
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
	class GraphicsManager;
	class Graphics : public systems::Component
	{
	public:
		enum class Type
		{
			Camera,
			MeshRenderer,
			SkinnedMeshRenderer
		};

		Graphics(String name, Type type) :
			systems::Component(name, true),
			m_type(type) {}
		~Graphics() = default;

	public:
		void Initialize() override;
		void Finalize() override;

	private:
		Type m_type;

	private:
		friend GraphicsManager;

	};
}
