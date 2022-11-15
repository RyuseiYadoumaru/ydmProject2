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
			DirectX::XMFLOAT3 m_Pos;	// �ʒu
			DirectX::XMFLOAT3 m_Normal;	// �@��
			DirectX::XMFLOAT2 m_Tex;	// UV���W
			int32_t	m_BoneIndex[4];		// �{�[���C���f�b�N�X
			float	m_BoneWeight[4];	// �E�F�C�g�l
			int32_t	m_BoneNum;			// �{�[����
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
		SharedPtr<Animation> m_animation	= nullptr;
		Vector<SharedPtr<AnimationClip>> m_animationClipList;
	};
}
