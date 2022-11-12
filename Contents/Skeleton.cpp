#include "Skeleton.h"
#include "../Assimpscene.h"
#include <assimp\scene.h>
#include "../dx11mathutil.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"

USING_GAME_SYSTEMS
USING_SYSTEMS;
USING_DIRECTX;

bool Skeleton::Load(AssimpScene* assimpScene)
{
	if (assimpScene == nullptr)
	{
		this->m_isLoad = false;
		return false;
	}

	// �{�[���z��p�̃��������m��
	this->m_bones.clear();
	this->m_bones.resize(assimpScene->GetBoneNum());

	// �{�[������
	CreateBones(assimpScene,
		assimpScene->GetScene()->mRootNode,
		Bone::NONE_PARENT);

	// �{�[���̐e�q�֌W���`��
	CreateBoneTree();

	// �{�[���I�t�Z�b�g�s�񏉊���
	InitBonesOffsetMatrix(assimpScene);
	this->m_isLoad = true;

	// �����{�[����ۑ�
	for (auto& boneMatrix : m_bones)
	{
		m_defaultBonesMatrix.emplace_back(boneMatrix.GetOffsetMatrix());
		m_bonesMatrix.emplace_back(boneMatrix.GetOffsetMatrix());
	}

	return true;
}

Bone* Skeleton::GetRootBone()
{
	return this->m_rootBone;
}

Bone* Skeleton::GetBoneByIndex(int index)
{
	return &m_bones[index];
}

int Skeleton::GetBoneNum() const
{
	return m_bones.size();
}

// �{�[���𐶐�
void Skeleton::CreateBones(AssimpScene* assimpScene, aiNode* node, int parentIndex)
{
	// ���O����{�[���z��̃C���f�b�N�X�ԍ����擾
	int boneIndex = assimpScene->GetBoneIndexByName(node->mName.C_Str());

	// �{�[������ۑ�����
	Bone& bone = m_bones[boneIndex];
	bone.SetParentIndex(parentIndex);
	bone.SetName(node->mName.C_Str());
	bone.SetBoneIndex(boneIndex);

	const unsigned int childCount = node->mNumChildren;
	for (int i = 0; i < childCount; i++)
	{
		aiNode* child = node->mChildren[i];
		CreateBones(assimpScene, child, boneIndex);
	}
}

// �{�[���̐e�q�֌W���`��
void Skeleton::CreateBoneTree()
{
	// ���[�g�{�[����ݒ�
	this->m_rootBone = &this->m_bones[0];

	const int boneNum = m_bones.size();
	for (int i = 0; i < boneNum; i++)
	{
		Bone* bone = &this->m_bones[i];

		// �e������Ύ������q�ɂ���
		const int parentIndex = this->m_bones[i].GetParentIndex();
		if (parentIndex != Bone::NONE_PARENT)
		{
			this->m_bones[parentIndex].AddChild(bone);
		}
	}
}

void Skeleton::InitBonesOffsetMatrix(AssimpScene* assimpScene)
{
	// ���b�V�����擾�̒��Ƀ{�[����񂪂܂���Ă���
	const int meshNum = assimpScene->GetScene()->mNumMeshes;
	for (int meshIndex = 0; meshIndex < meshNum; meshIndex++)
	{
		auto mesh = assimpScene->GetScene()->mMeshes[meshIndex];

		const int boneNum = mesh->mNumBones;
		for (int boneIndex = 0; boneIndex < boneNum; boneIndex++)
		{
			auto bone = mesh->mBones[boneIndex];
			int idx = assimpScene->GetBoneIndexByName(bone->mName.C_Str());

			DirectX::XMFLOAT4X4 offset = DX11MtxaiToDX(bone->mOffsetMatrix);
			m_bones[idx].SetOffsetMatrix(offset);
		}
	}
}

void Skeleton::CalcBonesMatrix(
	const std::vector<DirectX::XMFLOAT4X4>& animationMatrix,
	int index,
	DirectX::XMFLOAT4X4 parentMatrix,
	std::vector<DirectX::XMFLOAT4X4>& outputMatrix)
{
	DirectX::XMFLOAT4X4 worldMatrix;
	DX11MtxMultiply(
		worldMatrix,
		animationMatrix[index],
		parentMatrix);

	DirectX::XMFLOAT4X4 offsetMatrix;
	offsetMatrix = m_bones[index].GetOffsetMatrix();

	DirectX::XMFLOAT4X4 boneMatrix;
	DX11MtxMultiply(
		boneMatrix,
		offsetMatrix,
		worldMatrix);

	outputMatrix[index] = boneMatrix;

	const int childNum = m_bones[index].GetChildCount();
	for (int i = 0; i < childNum; i++)
	{
		Bone* child = m_bones[index].GetChild(i);
		CalcBonesMatrix(
			animationMatrix,
			child->GetBoneIndex(),
			worldMatrix,
			outputMatrix);
	}
}