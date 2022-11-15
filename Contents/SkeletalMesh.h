//*****************************************************************************
//* @file   SkeletalMesh.h
//* @brief  スケルタルメッシュ
//* @note   ボーン情報を所持しているメッシュクラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "MeshHeader.h"

namespace GAME_SYSTEMS
{
	class SkeletalMesh : public Mesh
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 m_Pos;	// 位置
			DirectX::XMFLOAT3 m_Normal;	// 法線
			DirectX::XMFLOAT2 m_Tex;	// UV座標
			int32_t	m_BoneIndex[4];		// ボーンインデックス
			float	m_BoneWeight[4];	// ウェイト値
			int32_t	m_BoneNum;			// ボーン数
		};

	public:
		virtual void Load(T_String meshName) override;
		virtual void Releace() override;
		virtual void Render() override;

		void SetAnimationClip(T_String animDataName);

	private:
		// ノード解析
		void ProcessNode(aiNode* node, AssimpScene* assimpScene);
		// メッシュ解析
		Polygon<SkeletalMesh::Vertex> ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx);

	private:
		Vector<Polygon<SkeletalMesh::Vertex>> m_meshList;
		SharedPtr<Skeleton> m_skeleton		= nullptr;
		SharedPtr<Animation> m_animation	= nullptr;
		Vector<SharedPtr<AnimationClip>> m_animationClipList;
	};
}
