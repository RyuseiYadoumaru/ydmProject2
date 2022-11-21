//*****************************************************************************
//* @file   SkeletalMesh.h
//* @brief  �X�P���^�����b�V��
//* @note   �{�[�������������Ă��郁�b�V���N���X
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
			DirectX::XMFLOAT3 m_Pos		= {0.0f, 0.0f, 0.0f};			// �ʒu
			DirectX::XMFLOAT3 m_Normal	= { 0.0f, 0.0f, 0.0f };			// �@��
			DirectX::XMFLOAT2 m_Tex		= { 0.0f, 0.0f };				// UV���W
			Int32	m_BoneIndex[4]		= { -1, -1, -1, -1 };			// �{�[���C���f�b�N�X
			Float32	m_BoneWeight[4]		= { 0.0f, 0.0f, 0.0f, 0.0f };	// �E�F�C�g�l
			Int32	m_BoneNum			= 0;							// �{�[����
		};

	public:
		virtual void Load(T_String meshName) override;
		virtual void Releace() override;
		virtual void Render() override;

		void SetAnimationClip(T_String animDataName);

	private:
		// �m�[�h���
		void ProcessNode(aiNode* node, AssimpScene* assimpScene);
		// ���b�V�����
		Polygon<SkeletalMesh::Vertex> ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx);

	private:
		Vector<Polygon<SkeletalMesh::Vertex>> m_meshList;
		SharedPtr<Skeleton> m_skeleton		= nullptr;
		SharedPtr<AnimationClip> m_animationClip = nullptr;
		SharedPtr<Animation> m_animation	= nullptr;
	};
}
