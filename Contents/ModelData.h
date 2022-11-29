//*****************************************************************************
//* @file   ModelData.h
//* @brief  
//* @note   3Dモデルの全てのデータ保持する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "../System/ThirdParty/Assimp/AssimpScene.h"
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class Model;
	class Skeleton;
	class Material;

	class ModelData
	{
		using ModelContainer	= Vector<SharedPtr<Model>>;

	public:
		void Load(T_String filePath);
		void Releace();

	public:
		// モデル
		SharedPtr<Model> GetModel(uInt32 index);

		// スケルトン
		SharedPtr<Skeleton> GetSkeleton() const noexcept { return m_skeleton; }
		bool HasBone() const noexcept { return m_hasBone; }

		// アニメーション
		bool HasAnimation() const noexcept { return m_hasAnimation; }

	public:
		ModelData() = default;
		~ModelData() = default;

	private:
		void ProcessNode(aiNode* node);

	private:
		// モデルデータのローダー
		SYSTEMS::AssimpScene m_modelLoader;

		// モデル
		ModelContainer m_modelList;
		Unordered_Map<T_String, uInt32> m_modelNameList;
		bool m_enableLoadLevelOfDetail = false;

		// スケルトン
		SharedPtr<Skeleton> m_skeleton = nullptr;
		bool m_hasBone = false;

		// アニメーション
		bool m_hasAnimation = false;

	};
}
