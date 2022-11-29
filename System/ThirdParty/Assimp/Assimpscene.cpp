//*****************************************************************************
//* @file   AssimpScene.cpp
//* @brief  
//* @note   Assimpでロードしたデータを管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "AssimpHeader.h"
#include "AssimpScene.h"
USING_SYSTEMS;

bool AssimpScene::Init(T_String filename) 
{
	m_Scene = aiImportFile(filename.c_str(),
		aiProcess_ConvertToLeftHanded |
		aiProcessPreset_TargetRealtime_MaxQuality);

	if (m_Scene == nullptr) 
	{
		return false;
	}

	CreateBoneIndexMap(m_Scene->mRootNode);
	return true;
}

void AssimpScene::Exit()
{
	aiReleaseImport(m_Scene);
}

const aiScene* AssimpScene::GetScene() const
{
	return m_Scene;
}

bool SYSTEMS::AssimpScene::HasMesh() const noexcept
{
	return m_Scene->HasMeshes();
}

uInt32 SYSTEMS::AssimpScene::GetMeshNum() const noexcept
{
	return m_Scene->mNumMeshes;
}

bool AssimpScene::HasAnimation() 
{
	return m_Scene->HasAnimations();
}

unsigned int AssimpScene::GetAnimationsNum() const
{
	return m_Scene->mNumAnimations;
}

int AssimpScene::GetBoneIndexByName(std::string name) const
{
	if (this->m_boneIndexMap.find(name) != this->m_boneIndexMap.end())
	{
		return m_boneIndexMap.at(name);
	}
	return -1;
}

uInt32 AssimpScene::GetBoneNum() const
{
	return static_cast<uInt32>(m_boneIndexMap.size());
}

void AssimpScene::CreateBoneIndexMap(aiNode* node)
{
	if (this->m_boneIndexMap.find(node->mName.C_Str()) != this->m_boneIndexMap.end())
	{
		return;
	}

	Int32 index = static_cast<Int32>(m_boneIndexMap.size());
	this->m_boneIndexMap.emplace(node->mName.C_Str(), index);

	const uInt32 childCount = node->mNumChildren;
	for (uInt32 i = 0; i < childCount; i++)
	{
		aiNode* child = node->mChildren[i];
		CreateBoneIndexMap(child);
	}
}