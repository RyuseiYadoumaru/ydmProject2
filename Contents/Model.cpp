//*****************************************************************************
//* @file   Model.cpp
//* @brief  
//* @note   ���f���f�[�^���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Model.h"
#include "ModelData.h"
#include "Mesh.h"
#include "Material.h"
#include "Skeleton.h"
#include "Debug.h"
#include "../System/ThirdParty/Assimp/AssimpScene.h"
#include "../System/ThirdParty/Assimp/AssimpHeader.h"


void GAME_SYSTEMS::Model::Load(const aiNode* assimpNode, const aiScene* assimpScene)
{
	// ���O�擾
	m_name = assimpNode->mName.C_Str();

	// ���b�V���̐����擾
	m_meshNum = assimpNode->mNumMeshes;
	m_meshDataList.resize(m_meshNum);

	// �m�[�h���̑S�Ẵ��b�V�����擾
	for (uInt32 num = 0; num < m_meshNum; num++)
	{
		uInt32 meshIndex = assimpNode->mMeshes[num];
		m_meshDataList[num] = std::make_shared<Mesh>();
		auto mesh = assimpScene->mMeshes[meshIndex];
		m_meshDataList[num]->Load(mesh, m_parent->GetSkeleton().get());
	}

	m_hasMesh = true;
}

void GAME_SYSTEMS::Model::LoadGeometry(Geometry type)
{
	if (type == Model::Geometry::Cube)
	{
		CreateCube();
	}
	else if (type == Model::Geometry::Sphare)
	{
		CreateSphare();
	}
	else if (type == Model::Geometry::Terrain)
	{
		CreateTerrain();
	}
}

void GAME_SYSTEMS::Model::Releace()
{
	m_parent = nullptr;
	for (auto& mesh : m_meshDataList)
	{
		mesh->Releace();
	}
	m_meshDataList.clear();
}

const SharedPtr<GAME_SYSTEMS::Mesh>& GAME_SYSTEMS::Model::GetMeshData(uInt32 index) noexcept
{
	if (index >= m_meshDataList.size() || m_meshDataList.empty() == true)
	{
		TOOLS::Debug::Assert(true, TEXT("���b�V���̎Q�ƂɎ��s���܂���"));
		return nullptr;
	}

	return m_meshDataList[index];
}

void GAME_SYSTEMS::Model::CreateCube()
{
}

void GAME_SYSTEMS::Model::CreateSphare()
{
}

void GAME_SYSTEMS::Model::CreateTerrain()
{
}
