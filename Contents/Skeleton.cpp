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
	// メッシュ情報取得
	auto mesh = assimpScene->mMeshes[0];

	// ボーンインデックス生成
	// 現在全てのノードを取得してボーンマップを生成しているため
	// ボーンの情報のみ取得できるようにする仕組みにしたい…
	auto rootNode = assimpScene->mRootNode;
	CreateBoneIndexList(rootNode);

	// ボーン生成
	m_boneList.clear();
	uInt32 boneSize = m_boneIndexList.size();
	m_boneList.resize(boneSize);
	CreateBoneList(assimpScene, rootNode, Bone::NONE_PARENT);
 
	// ルートボーンを設定
	m_rootBone = &m_boneList[0];

	// ボーンの親子関係を形成
	for (Int32 i = 0; i < m_boneList.size(); i++)
	{
		Bone* bone = &m_boneList[i];
		// 親がいれば自分を子にする
		const Int32 parentIndex = m_boneList[i].GetParentIndex();
		if (parentIndex != Bone::NONE_PARENT)
		{
			m_boneList[parentIndex].AddChild(bone);
		}
	}
	// ボーンオフセット行列初期化
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
	// 初期ボーンを保存
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

void GAME_SYSTEMS::Skeleton::UpdateBoneMatrix()
{
	CalcBonesMatrix(m_rootBone->GetBoneIndex(), MY_MATH::Matrix4x4::CreateMatrixIdentity());
}


Int32 GAME_SYSTEMS::Skeleton::GetBoneIndexByName(T_String boneName) noexcept
{
	if (m_boneIndexList.contains(boneName) == false)
	{
		return -1;
	}
	return m_boneIndexList[boneName];
}


void Skeleton::CreateBoneList(const aiScene* assimpScene, const aiNode* node, uInt32 parentIndex)
{
	// 名前からボーン配列のインデックス番号を取得
	Int32 boneIndex = GetBoneIndexByName(node->mName.C_Str());

	// ボーン情報を保存する
	if (boneIndex != -1)
	{
		m_boneList[boneIndex].SetParentIndex(parentIndex);
		m_boneList[boneIndex].SetName(node->mName.C_Str());
		m_boneList[boneIndex].SetBoneIndex(boneIndex);
	}

	// 子ボーンも生成する
	const uInt32 childCount = node->mNumChildren;
	for (uInt32 i = 0; i < childCount; i++)
	{
		aiNode* child = node->mChildren[i];
		CreateBoneList(assimpScene, child, boneIndex);
	}
}

void GAME_SYSTEMS::Skeleton::CreateBoneIndexList(const aiNode* node)
{
	// リスト探索
	auto nodeName = node->mName.C_Str();
	if (m_boneIndexList.contains(nodeName) == true)
	{
		return;
	}

	// ボーンマップ追加
	Int32 index = static_cast<Int32>(m_boneIndexList.size());
	m_boneIndexList.emplace(nodeName, index);

	// 子供も探索
	const uInt32 childCount = node->mNumChildren;
	for (uInt32 i = 0; i < childCount; i++)
	{
		aiNode* child = node->mChildren[i];
		CreateBoneIndexList(child);
	}
}


void Skeleton::CalcBonesMatrix(Int32 index, MY_MATH::Matrix4x4 parentMatrix)
{
	// 親ボーンと組み合わせる
	MY_MATH::Matrix4x4 boneTransformMatrix = m_boneList[index].GetBoneMatrix();
	MY_MATH::Matrix4x4 worldMatrix = MY_MATH::Matrix4x4::MatrixMultiply(boneTransformMatrix, parentMatrix);

	// ボーン行列生成
	MY_MATH::Matrix4x4 offsetMatrix = m_boneList[index].GetOffsetMatrix();
	MY_MATH::Matrix4x4 boneMatrix = MY_MATH::Matrix4x4::MatrixMultiply(offsetMatrix, worldMatrix);
	m_bonesMatrixList[index] = boneMatrix;

	// 子ボーンの行列計算
	const Int32 childNum = m_boneList[index].GetChildCount();
	for (Int32 i = 0; i < childNum; i++)
	{
		Bone* child = m_boneList[index].GetChild(i);
		CalcBonesMatrix(child->GetBoneIndex(), worldMatrix);
	}
}