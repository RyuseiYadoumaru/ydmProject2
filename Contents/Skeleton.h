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

namespace GAME_SYSTEMS
{
	class Skeleton
	{
	public:
		bool Load(AssimpScene* assimpScene);
		void CreateAnimationMatrix(const Vector<MY_MATH::Matrix4x4>& animMtxList);
		void InitDefaultMatrix();

	public:
		Vector<MY_MATH::Matrix4x4>& GetBonesMatrix()  noexcept { return m_bonesMatrix; }
		Bone* GetRootBone() noexcept { return m_rootBone; }
		Bone* GetBoneByIndex(Int32 index) noexcept { return &m_boneList[index]; }
		Int32 GetBoneNum() const noexcept { return static_cast<Int32>(m_boneList.size()); };

	private:
		// ボーン行列作成
		void CalcBonesMatrix(
			const Vector<MY_MATH::Matrix4x4>& animationMatrix,
			Int32 index,
			MY_MATH::Matrix4x4 parentMatrix,
			Vector<MY_MATH::Matrix4x4>& outputMatrix);


		// ボーンを生成
		void CreateBoneList(AssimpScene* assimpScene, aiNode* node, Int32 parentIndex);

		// ボーンの親子関係を形成
		void CreateBoneTree();

		// ボーンオフセット行列初期化
		void InitBonesOffsetMatrix(AssimpScene* assimpScene);

	private:
		// ボーン配列
		Vector<Bone> m_boneList;
		// デフォルトボーン行列
		Vector<MY_MATH::Matrix4x4> m_defaultBonesMatrix;
		// 現在のボーン行列
		Vector<MY_MATH::Matrix4x4> m_bonesMatrix;
		
		Bone* m_rootBone = nullptr;		// ルートとなるボーン
		bool m_isLoad = false;			// 初期化したかどうか
	};
}
