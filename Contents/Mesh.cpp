//*****************************************************************************
//* @file   Mesh.cpp
//* @brief  
//* @note   メッシュに必要な情報を管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Mesh.h"
#include "Skeleton.h"
#include "Debug.h"
#include "../System/MeshInfo.h"
#include "../System/ThirdParty/Assimp/AssimpHeader.h"

void GAME_SYSTEMS::Mesh::Load(const aiMesh* assimpMesh, Skeleton* skeleton)
{
	// 頂点数取得
	m_vertexNum = assimpMesh->mNumVertices;

	// メッシュの名前取得
	m_meshName = assimpMesh->mName.C_Str();

	// 頂点情報取得
	m_vertexDataList.resize(m_vertexNum);
	for (uInt32 i = 0; i < m_vertexNum; i++)
	{
		SharedPtr<SYSTEMS::VertexData> vertex;
		vertex = std::make_shared<SYSTEMS::VertexData>();

		// 頂点座標
		vertex->Position.x = assimpMesh->mVertices[i].x;
		vertex->Position.y = assimpMesh->mVertices[i].y;
		vertex->Position.z = assimpMesh->mVertices[i].z;

		// カラー
		if (assimpMesh->HasVertexColors(0) == true)
		{
			vertex->Color.r = assimpMesh->mColors[0]->r;
			vertex->Color.g = assimpMesh->mColors[0]->g;
			vertex->Color.b = assimpMesh->mColors[0]->b;
			vertex->Color.a = assimpMesh->mColors[0]->a;
		}

		// 法線
		if (assimpMesh->HasNormals() == true)
		{
			vertex->Normal.x = assimpMesh->mNormals[i].x;
			vertex->Normal.y = assimpMesh->mNormals[i].y;
			vertex->Normal.z = assimpMesh->mNormals[i].z;
		}
		else
		{
			vertex->Normal = vertex->Position;
		}

		// テクスチャ
		if (assimpMesh->HasTextureCoords(0) == true)
		{
			vertex->Texcoord.x = assimpMesh->mTextureCoords[0][i].x;
			vertex->Texcoord.y = assimpMesh->mTextureCoords[0][i].y;
		}

		// 頂点データセット
		m_vertexDataList[i] = vertex;
	}

	// ボーン情報取得
	m_boneNum = assimpMesh->mNumBones;
	if (m_boneNum > 0)
	{
		for (uInt32 num = 0; num < m_boneNum; num++)
		{
			// メッシュからボーン情報を取得
			auto bone = assimpMesh->mBones[num];
			for (uInt32 index = 0; index < bone->mNumWeights; index++)
			{
				// ウエイトに関連づいてる頂点idx
				auto weight = bone->mWeights[index];
				uInt32 vertexId = weight.mVertexId;
				// ボーン数
				uInt32 boneNum = m_vertexDataList[vertexId]->BoneNum;

				m_vertexDataList[vertexId]->BoneWeight[boneNum] = weight.mWeight;
				m_vertexDataList[vertexId]->BoneIndex[boneNum] = skeleton->GetBoneIndexByName(bone->mName.C_Str());
				m_vertexDataList[vertexId]->BoneNum++;

				TOOLS::Debug::Assert(m_vertexDataList[vertexId]->BoneNum > 4);
			}
		}
		m_hasBone = true;
	}

	// 面構成情報取得
	m_faceNum = assimpMesh->mNumFaces;
	m_faceList.resize(m_faceNum);
	for (uInt32 i = 0; i < assimpMesh->mNumFaces; i++)
	{
		auto face = assimpMesh->mFaces[i];
		m_faceList[i] = std::make_shared<SYSTEMS::Face>();
		for (uInt32 j = 0; j < face.mNumIndices; j++)
		{
			m_faceList[i]->Indices.emplace_back(face.mIndices[j]);
		}
	}
}

void GAME_SYSTEMS::Mesh::Releace()
{
	m_vertexNum = 0;
	m_vertexDataList.clear();
	m_faceList.clear();
}
