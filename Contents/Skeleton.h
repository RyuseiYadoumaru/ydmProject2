//*****************************************************************************
//* @file   Skeleton.h
//* @brief  
//* @note	�{�[���̏W����
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
			const std::vector<MY_MATH::Matrix4x4>& animationMatrix,
			int index,
			MY_MATH::Matrix4x4 parentMatrix,
			std::vector<MY_MATH::Matrix4x4>& outputMatrix);

	public:
		Vector<MY_MATH::Matrix4x4>& GetBonesMatrix()  noexcept { return m_bonesMatrix; }
		Bone* GetRootBone() noexcept { return m_rootBone; }
		Bone* GetBoneByIndex(Int32 index) noexcept { return &m_boneList[index]; }
		Int32 GetBoneNum() const noexcept { return static_cast<uInt32>(m_boneList.size()); };

	private:
		// �{�[���𐶐�
		void CreateBoneList(AssimpScene* assimpScene, aiNode* node, Int32 parentIndex);

		// �{�[���̐e�q�֌W���`��
		void CreateBoneTree();

		// �{�[���I�t�Z�b�g�s�񏉊���
		void InitBonesOffsetMatrix(AssimpScene* assimpScene);

	private:
		// �{�[���z��
		Vector<Bone> m_boneList;
		// �f�t�H���g�{�[���s��
		Vector<MY_MATH::Matrix4x4> m_defaultBonesMatrix;
		// ���݂̃{�[���s��
		Vector<MY_MATH::Matrix4x4> m_bonesMatrix;
		
		Bone* m_rootBone = nullptr;		// ���[�g�ƂȂ�{�[��
		bool m_isLoad = false;			// �������������ǂ���
	};
}
