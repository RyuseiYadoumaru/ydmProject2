//*****************************************************************************
//* @file   AssimpScene.h
//* @brief  
//* @note   Assimpでロードしたデータを管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiBone;
struct aiFace;


namespace SYSTEMS
{
	class AssimpScene
	{
	public:
		// 初期処理
		bool Init(T_String filename);
		// 終了処理
		void Exit();

		// シーン取得
		const aiScene* GetScene() const;

		// メッシュ
		bool HasMesh() const noexcept;
		uInt32 GetMeshNum() const noexcept;

		// アニメーション
		bool HasAnimation();
		uInt32 GetAnimationsNum() const;

	private:
		const aiScene* m_Scene = nullptr;

		// ボーンの名前とインデックスを関連付ける
		Unordered_Map<T_String, int> m_boneIndexList;
	};
}