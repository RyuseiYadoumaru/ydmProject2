//*****************************************************************************
//* @file   ModelData.cpp
//* @brief  
//* @note   3Dモデルの全てのデータ保持する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "ModelData.h"
#include "Model.h"
#include "Skeleton.h"
#include "AnimationClip.h"
#include "Material.h"
#include "Debug.h"
#include "../System/ThirdParty/Assimp/AssimpHeader.h"

void GAME_SYSTEMS::ModelData::Load(T_String filePath)
{
	// モデル情報取得
	m_modelLoader.Init(filePath);
	auto modelScene = m_modelLoader.GetScene();

	// スケルトン取得
	m_hasBone = modelScene->mMeshes[0]->HasBones();
	if (m_hasBone == true)
	{
		m_skeleton = std::make_shared<Skeleton>(this);
		m_skeleton->Load(modelScene);
	}

	// アニメーション取得
	if (modelScene->HasAnimations() == true)
	{
		m_animationClip = std::make_shared<AnimationClip>();
		m_animationClip->Load(modelScene->mAnimations[0]);
		m_animationClip->CalcAnimationTransform(m_skeleton.get(), 0.0f);
	}

	// ノード解析
	ProcessNode(modelScene->mRootNode);

	m_modelLoader.Exit();
}

void GAME_SYSTEMS::ModelData::Releace()
{
	for (auto& model : m_modelList)
	{
		model->Releace();
	}

	m_skeleton->Releace();
	m_skeleton = nullptr;
	m_modelList.clear();
	m_modelNameList.clear();
}

SharedPtr<GAME_SYSTEMS::Model> GAME_SYSTEMS::ModelData::GetModel(uInt32 index)
{
	if (index >= m_modelList.size() || m_modelList.empty() == true)
	{
		TOOLS::Debug::Assert(true, "モデルの参照エラー");
		return nullptr;
	}
	return m_modelList[index];
}

void GAME_SYSTEMS::ModelData::ProcessNode(aiNode* node)
{
	// メッシュ取得
	if (node->mNumMeshes > 0 && m_modelLoader.HasMesh() == true)
	{
		if (m_enableLoadLevelOfDetail == true || m_modelList.empty() == true)
		{
			// LODが有効か空の時モデルを生成する
			SharedPtr<Model> addModel = std::make_shared<Model>(this);
			addModel->Load(node, m_modelLoader.GetScene());
			m_modelList.emplace_back(addModel);
			m_modelNameList[node->mName.C_Str()] = static_cast<uInt32>(m_modelList.size()) - 1;
		}
	}

	// 子ノード解析
	for (uInt32 num = 0; num < node->mNumChildren; num++)
	{
		ProcessNode(node->mChildren[num]);
	}
}
