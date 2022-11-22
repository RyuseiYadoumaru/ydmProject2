//*****************************************************************************
//* @file   Skeleton.cpp
//* @brief  
//* @note	ボーンの集合体
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include <assimp\scene.h>
#include <assimp/mesh.h>
#include "Skeleton.h"
#include "Debug.h"
#include "../System/ThirdParty/Assimp/Assimpscene.h"
#include "../dx11mathutil.h"
#include "../System/Shader.h"
#include "../System/DirectXGraphics.h"
#include "../System/MessageWindow.h"

USING_GAME_SYSTEMS
USING_SYSTEMS;
USING_DIRECTX;

bool Skeleton::Load(AssimpScene* assimpScene)
{
	if (assimpScene == nullptr)
	{
		m_isLoad = false;
		MessageWindow::GetInstance()->Error("Assimpのデータがありません");
		TOOLS::Debug::Assert(assimpScene == nullptr);
		return false;
	}

	// ボーン配列用のメモリを確保
	m_boneList.clear();
	m_boneList.resize(assimpScene->GetBoneNum());

	// 親ボーン生成
	CreateBoneList(assimpScene,
		assimpScene->GetScene()->mRootNode,
		Bone::NONE_PARENT);

	// ボーンの親子関係を形成
	CreateBoneTree();

	// ボーンオフセット行列初期化
	InitBonesOffsetMatrix(assimpScene);
	m_isLoad = true;

	// 初期ボーンを保存
	for (auto& boneMatrix : m_boneList)
	{
		m_defaultBonesMatrix.emplace_back(boneMatrix.GetOffsetMatrix());
		m_bonesMatrix.emplace_back(boneMatrix.GetOffsetMatrix());
	}

	//CalcBonesMatrix(
	//	m_defaultBonesMatrix,
	//	m_rootBone->GetBoneIndex(),
	//	MY_MATH::Matrix4x4::CreateMatrixIdentity(),
	//	m_bonesMatrix);

	return true;
}

void GAME_SYSTEMS::Skeleton::CreateAnimationMatrix(const Vector<MY_MATH::Matrix4x4>& animMtxList)
{
	CalcBonesMatrix(
		animMtxList,
		m_rootBone->GetBoneIndex(),
		MY_MATH::Matrix4x4::CreateMatrixIdentity(),
		m_bonesMatrix);
}

void GAME_SYSTEMS::Skeleton::InitDefaultMatrix()
{
	m_defaultBonesMatrix = m_bonesMatrix;
}

// ボーンを生成
void Skeleton::CreateBoneList(AssimpScene* assimpScene, aiNode* node, Int32 parentIndex)
{
	// 名前からボーン配列のインデックス番号を取得
	Int32 boneIndex = assimpScene->GetBoneIndexByName(node->mName.C_Str());

	// ボーン情報を保存する
	m_boneList[boneIndex].SetParentIndex(parentIndex);
	m_boneList[boneIndex].SetName(node->mName.C_Str());
	m_boneList[boneIndex].SetBoneIndex(boneIndex);

	// 子ボーンも生成する
	const uInt32 childCount = node->mNumChildren;
	for (uInt32 i = 0; i < childCount; i++)
	{
		aiNode* child = node->mChildren[i];
		CreateBoneList(assimpScene, child, boneIndex);
	}
}

// ボーンの親子関係を形成
void Skeleton::CreateBoneTree()
{
	// ルートボーンを設定
	m_rootBone = &m_boneList[0];

	for (int i = 0; i < m_boneList.size(); i++)
	{
		Bone* bone = &m_boneList[i];
		// 親がいれば自分を子にする
		const Int32 parentIndex = m_boneList[i].GetParentIndex();
		if (parentIndex != Bone::NONE_PARENT)
		{
			this->m_boneList[parentIndex].AddChild(bone);
		}
	}
}

void Skeleton::InitBonesOffsetMatrix(AssimpScene* assimpScene)
{
	// メッシュ情報取得の中にボーン情報がまぎれている
	const Int32 meshNum = assimpScene->GetScene()->mNumMeshes;
	for (Int32 meshIndex = 0; meshIndex < meshNum; meshIndex++)
	{
		auto mesh = assimpScene->GetScene()->mMeshes[meshIndex];

		const Int32 boneNum = mesh->mNumBones;
		for (int boneIndex = 0; boneIndex < boneNum; boneIndex++)
		{
			auto bone = mesh->mBones[boneIndex];
			Int32 idx = assimpScene->GetBoneIndexByName(bone->mName.C_Str());

			MY_MATH::Matrix4x4 offset = MY_MATH::Matrix4x4::CreateMatrixFromAIMatrix(bone->mOffsetMatrix);
			m_boneList[idx].SetOffsetMatrix(offset);
		}
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
	outputMatrix[index] = boneMatrix;
	const Int32 childNum = m_boneList[index].GetChildCount();
	for (Int32 i = 0; i < childNum; i++)
	{
		Bone* child = m_boneList[index].GetChild(i);
		CalcBonesMatrix(
			animationMatrix,
			child->GetBoneIndex(),
			worldMatrix,
			outputMatrix);
	}
}