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

		// �{�[���𐶐�
		void CreateBones(AssimpScene* assimpScene, aiNode* node, int parentIndex);

		// �{�[���̐e�q�֌W���`��
		void CreateBoneTree();

		// �{�[���I�t�Z�b�g�s�񏉊���
		void InitBonesOffsetMatrix(AssimpScene* assimpScene);

	private:
		Vector<Bone> m_bones;	// �{�[���z��
		Vector<DirectX::XMFLOAT4X4> m_defaultBonesMatrix;
		Vector<DirectX::XMFLOAT4X4> m_bonesMatrix;
		Bone* m_rootBone;		// ���[�g�ƂȂ�{�[��
		bool m_isLoad = false;	// �������������ǂ���
	};
}
