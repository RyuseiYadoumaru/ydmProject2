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