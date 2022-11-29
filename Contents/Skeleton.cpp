//*****************************************************************************
//* @file   Skeleton.cpp
//* @brief  
//* @note	�{�[���̏W����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include <assimp\scene.h>
#include <assimp/mesh.h>
#include "Skeleton.h"
#include "Debug.h"
#include "../System/ThirdParty/Assimp/AssimpScene.h"
#include "../dx11mathutil.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"
#include "../System/MessageWindow.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;
USING_DIRECTX;

bool Skeleton::Load(const aiScene* assimpScene)
{
	// ���b�V�����擾
	auto mesh = assimpScene->mMeshes[0];

	// �{�[���C���f�b�N�X����
	m_boneNum = mesh->mNumBones;
	for (uInt32 num = 0; num < m_boneNum; num++)
	{
		T_String boneName = mesh->mBones[num]->mName.C_Str();
		m_boneIndexList.emplace(boneName, num);
	}

	// �e�{�[������
	m_boneList.clear();
	m_boneList.resize(m_boneNum);
	CreateBoneList(assimpScene,
		assimpScene->mRootNode,
		Bone::NONE_PARENT);
 
	// ���[�g�{�[����ݒ�
	m_rootBone = &m_boneList[0];

	// �{�[���̐e�q�֌W���`��
	for (Int32 i = 0; i < m_boneList.size(); i++)
	{
		Bone* bone = &m_boneList[i];
		// �e������Ύ������q�ɂ���
		const Int32 parentIndex = m_boneList[i].GetParentIndex();
		if (parentIndex != Bone::NONE_PARENT)
		{
			m_boneList[parentIndex].AddChild(bone);
		}
	}
	// �{�[���I�t�Z�b�g�s�񏉊���
	const Int32 meshNum = assimpScene->mNumMeshes;
	for (Int32 meshIndex = 0; meshIndex < meshNum; meshIndex++)
	{
		auto mesh = assimpScene->mMeshes[meshIndex];

		const Int32 boneNum = mesh->mNumBones;
		for (Int32 boneIndex = 0; boneIndex < boneNum; boneIndex++)
		{
			auto bone = mesh->mBones[boneIndex];
			Int32 index = GetBoneIndexByName(bone->mName.C_Str());

			MY_MATH::Matrix4x4 offset = MY_MATH::Matrix4x4::CreateMatrixFromAIMatrix(bone->mOffsetMatrix);
			m_boneList[index].SetOffsetMatrix(offset);
		}
	}
	// �����{�[����ۑ�
	for (auto& boneMatrix : m_boneList)
	{
		m_defaultBonesMatrixList.emplace_back(boneMatrix.GetOffsetMatrix());
		m_bonesMatrixList.emplace_back(boneMatrix.GetOffsetMatrix());
	}
	return true;
}

void GAME_SYSTEMS::Skeleton::Releace()
{
	m_rootBone = nullptr;
	m_parent = nullptr;
	m_boneList.clear();
	m_boneIndexList.clear();
	m_bonesMatrixList.clear();
	m_defaultBonesMatrixList.clear();
}


void GAME_SYSTEMS::Skeleton::CreateAnimationMatrix(const Vector<MY_MATH::Matrix4x4>& animMtxList)
{
	CalcBonesMatrix(
		animMtxList,
		m_rootBone->GetBoneIndex(),
		MY_MATH::Matrix4x4::CreateMatrixIdentity(),
		m_bonesMatrixList);
}


uInt32 GAME_SYSTEMS::Skeleton::GetBoneIndexByName(T_String boneName) noexcept
{
	if (m_boneIndexList.contains(boneName) == false)
	{
		return -1;
	}
	return m_boneIndexList[boneName];
}


void Skeleton::CreateBoneList(const aiScene* assimpScene, const aiNode* node, uInt32 parentIndex)
{
	// ���O����{�[���z��̃C���f�b�N�X�ԍ����擾
	Int32 boneIndex = GetBoneIndexByName(node->mName.C_Str());

	// �{�[������ۑ�����
	if (boneIndex != -1)
	{
		m_boneList[boneIndex].SetParentIndex(parentIndex);
		m_boneList[boneIndex].SetName(node->mName.C_Str());
		m_boneList[boneIndex].SetBoneIndex(boneIndex);
	}

	// �q�{�[������������
	const uInt32 childCount = node->mNumChildren;
	for (uInt32 i = 0; i < childCount; i++)
	{
		aiNode* child = node->mChildren[i];
		CreateBoneList(assimpScene, child, boneIndex);
	}
}


void Skeleton::CalcBonesMatrix(
	const Vector<MY_MATH::Matrix4x4>& animationMatrix,
	Int32 index,
	MY_MATH::Matrix4x4 parentMatrix,
	Vector<MY_MATH::Matrix4x4>& outputMatrix)
{
	MY_MATH::Matrix4x4 animMatrix = animationMatrix[index];
	MY_MATH::Matrix4x4 worldMatrix = MY_MATH::Matrix4x4::MatrixMultiply(animMatrix, parentMatrix);

	MY_MATH::Matrix4x4 offsetMatrix;
	offsetMatrix = m_boneList[index].GetOffsetMatrix();

	MY_MATH::Matrix4x4 boneMatrix = MY_MATH::Matrix4x4::MatrixMultiply(offsetMatrix, worldMatrix);
	m_bonesMatrixList[index] = boneMatrix;
	const Int32 childNum = m_boneList[index].GetChildCount();
	for (Int32 i = 0; i < childNum; i++)
	{
		Bone* child = m_boneList[index].GetChild(i);
		CalcBonesMatrix(
			animationMatrix,
			child->GetBoneIndex(),
			worldMatrix,
			m_bonesMatrixList);
	}
}