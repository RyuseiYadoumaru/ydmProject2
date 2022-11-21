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
			DirectX::XMFLOAT3 m_Pos		= {0.0f, 0.0f, 0.0f};			// 位置
			DirectX::XMFLOAT3 m_Normal	= { 0.0f, 0.0f, 0.0f };			// 法線
			DirectX::XMFLOAT2 m_Tex		= { 0.0f, 0.0f };				// UV座標
			Int32	m_BoneIndex[4]		= { -1, -1, -1, -1 };			// ボーンインデックス
			Float32	m_BoneWeight[4]		= { 0.0f, 0.0f, 0.0f, 0.0f };	// ウェイト値
			Int32	m_BoneNum			= 0;							// ボーン数
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
		SharedPtr<AnimationClip> m_animationClip = nullptr;
		SharedPtr<Animation> m_animation	= nullptr;
	};
}
