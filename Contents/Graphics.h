//*****************************************************************************
//* @file   Graphics.h
//* @brief  
//* @note   �O���t�B�b�N����̃R���|�[�l���g�̊��N���X
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
	class SceneManager;
	class Graphics : public systems::Component
	{
	public:
		enum class Type
		{
			Camera,
			MeshRenderer
		};

		Graphics(String name, Type type) :
			systems::Component(name, true),
			m_type(type) {}
		~Graphics() = default;

	private:
		static bool GraphicsUpdate();
		static bool GraphicsReleace();

	private:
		static Map<Type, Unordered_Map<uInt32, Graphics*>> m_graphicsList;;

	public:
		void Initialize() override;
		void Finalize() override;

	private:
		Type m_type;

	private:
		friend GameObjectManager;
		friend SceneManager;

	};
}
