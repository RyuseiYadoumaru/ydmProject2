//*****************************************************************************
//* @file   ModelData.cpp
//* @brief  
//* @note   3D���f���̑S�Ẵf�[�^�ێ�����
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
	// ���f�����擾
	m_modelLoader.Init(filePath);
	auto modelScene = m_modelLoader.GetScene();

	// �X�P���g���擾
	m_hasBone = modelScene->mMeshes[0]->HasBones();
	if (m_hasBone == true)
	{
		m_skeleton = std::make_shared<Skeleton>(this);
		m_skeleton->Load(modelScene);
	}

	// �A�j���[�V�����擾
	if (modelScene->HasAnimations() == true)
	{
		m_animationClip = std::make_shared<AnimationClip>();
		m_animationClip->Load(modelScene->mAnimations[0]);
		m_animationClip->CalcAnimationTransform(m_skeleton.get(), 0.0f);
	}

	// �m�[�h���
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
		TOOLS::Debug::Assert(true, "���f���̎Q�ƃG���[");
		return nullptr;
	}
	return m_modelList[index];
}

void GAME_SYSTEMS::ModelData::ProcessNode(aiNode* node)
{
	// ���b�V���擾
	if (node->mNumMeshes > 0 && m_modelLoader.HasMesh() == true)
	{
		if (m_enableLoadLevelOfDetail == true || m_modelList.empty() == true)
		{
			// LOD���L������̎����f���𐶐�����
			SharedPtr<Model> addModel = std::make_shared<Model>(this);
			addModel->Load(node, m_modelLoader.GetScene());
			m_modelList.emplace_back(addModel);
			m_modelNameList[node->mName.C_Str()] = static_cast<uInt32>(m_modelList.size()) - 1;
		}
	}

	// �q�m�[�h���
	for (uInt32 num = 0; num < node->mNumChildren; num++)
	{
		ProcessNode(node->mChildren[num]);
	}
}
