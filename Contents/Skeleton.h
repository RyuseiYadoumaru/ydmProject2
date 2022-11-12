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

		void CalcBonesMatrix(
			const std::vector<DirectX::XMFLOAT4X4>& animationMatrix,
			int index,
			DirectX::XMFLOAT4X4 parentMatrix,
			std::vector<DirectX::XMFLOAT4X4>& outputMatrix);

	public:
		Vector<DirectX::XMFLOAT4X4>& GetBonesMatrix() noexcept { return m_bonesMatrix; }
		Bone* GetRootBone();
		Bone* GetBoneByIndex(int index);
		int GetBoneNum() const;

	private:

		// ボーンを生成
		void CreateBones(AssimpScene* assimpScene, aiNode* node, int parentIndex);

		// ボーンの親子関係を形成
		void CreateBoneTree();

		// ボーンオフセット行列初期化
		void InitBonesOffsetMatrix(AssimpScene* assimpScene);

	private:
		Vector<Bone> m_bones;	// ボーン配列
		Vector<DirectX::XMFLOAT4X4> m_defaultBonesMatrix;
		Vector<DirectX::XMFLOAT4X4> m_bonesMatrix;
		Bone* m_rootBone;		// ルートとなるボーン
		bool m_isLoad = false;	// 初期化したかどうか
	};
}
