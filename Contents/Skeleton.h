//*****************************************************************************
//* @file   Skeleton.h
//* @brief  
//* @note	ボーンの集合体
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "Bone.h"
#include "macro.h"
#include "std.h"

struct aiNode;
struct aiMesh;
struct aiScene;

namespace GAME_SYSTEMS
{
	class ModelData;

	class Skeleton
	{
	public:
		bool Load(const aiScene* assimpScene);
		void Releace();
		void UpdateBoneMatrix();

	public:
		// ボーン取得
		Bone* GetRootBone() noexcept { return m_rootBone; }
		Bone* GetBoneByIndex(Int32 index) noexcept { return &m_boneList[index]; }
		Int32 GetBoneNum() const noexcept { return static_cast<Int32>(m_boneList.size()); };

		// ボーンインデックス取得
		Int32 GetBoneIndexByName(T_String boneName) noexcept;

		// ボーン行列取得
		Vector<MY_MATH::Matrix4x4>& GetBonesMatrix()  noexcept { return m_bonesMatrixList; }

	public:
		explicit Skeleton(ModelData* modelData) : m_parent(modelData) {}
		~Skeleton() = default;

	private:
		// ボーン行列作成
		void CalcBonesMatrix(Int32 index, MY_MATH::Matrix4x4 parentMatrix);

		// ボーンを生成
		void CreateBoneList(const aiScene* assimpScene, const aiNode* node, uInt32 parentIndex);

	private:
		// 親データ
		ModelData* m_parent	 = nullptr;
		
		// ボーン
		Bone* m_rootBone = nullptr;
		uInt32 m_boneNum = 0;
		Vector<Bone> m_boneList;
		Unordered_Map<T_String, uInt32> m_boneIndexList;
		
		// デフォルトボーン行列
		Vector<MY_MATH::Matrix4x4> m_defaultBonesMatrixList;
		// 現在のボーン行列
		Vector<MY_MATH::Matrix4x4> m_bonesMatrixList;
	};
}
