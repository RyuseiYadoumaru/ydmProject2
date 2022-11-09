//*****************************************************************************
//* @file   Scene.h
//* @brief  シーンのベースクラス
//* @note   全てのシーンのもととなる。シーンを生成するときはここから生成する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once

#include "SceneHeader.h"


#define SCENE_CLASS using gameSystems::Scene::Scene;

namespace GAME_SYSTEMS
{	
	class Scene : public systems::Object
	{
	public:
		bool Initialize();
		bool Run();
		bool Finalize();
		virtual void Render()		= 0;

	public:
		OBJECT_CLASS;

	public:
		// ディスプレイカラー
		void SetDisplayColor(myMath::Color& color) noexcept { m_displayColor = color; }
		void SetDisplayColor(Float32 red, Float32 green, Float32 blue) noexcept { m_displayColor.Set(red, green, blue, 1.0f); }
		const myMath::Color& GetDisPlayColor() const noexcept { return m_displayColor; }

		virtual void BeginPlay()	= 0;

	protected:
		virtual void ObjectEntry()	= 0;
		virtual void Tick()			= 0;
		virtual void EndPlay()		= 0;

	private:
		bool SceneSetUp();
		bool SceneShutdown();


	private:
		myMath::Color m_displayColor;
	};
}
