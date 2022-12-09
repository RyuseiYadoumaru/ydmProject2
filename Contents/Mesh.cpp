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
#include "../System/ThirdParty/Assimp/AssimpHeader.h"
#include "../System/MeshInfo.h"

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

void GAME_SYSTEMS::Mesh::LoadCube(Float32 meshSize)
{
	// 頂点生成
	m_faceNum = 6;
	m_vertexNum = m_faceNum * 6;
	Float32 size = meshSize * 1.0f;
	Vector<SYSTEMS::VertexData> vertexList;
	Vector<uInt32> indexList;
	vertexList.resize(m_vertexNum);
	indexList.resize(m_vertexNum);

	// 手前
	vertexList[0].Position.Set( size,  size, -size);
	vertexList[1].Position.Set( size,  size, -size);
	vertexList[2].Position.Set( size, -size, -size);
	vertexList[3].Position.Set( size, -size, -size);
	vertexList[4].Position.Set(-size, -size, -size);
	vertexList[5].Position.Set(-size,  size, -size);
	indexList[0] = 0;
	indexList[1] = 1;
	indexList[2] = 2;
	indexList[3] = 3;
	indexList[4] = 0;
	indexList[5] = 2;

	// 奥
	vertexList[6].Position.Set (-size,  size, size);
	vertexList[7].Position.Set ( size,  size, size);
	vertexList[8].Position.Set ( size, -size, size);
	vertexList[9].Position.Set ( size, -size, size);
	vertexList[10].Position.Set(-size, -size, size);
	vertexList[11].Position.Set(-size,  size, size);
	indexList[6] = 4;
	indexList[7] = 5;
	indexList[8] = 6;
	indexList[9] = 7;
	indexList[10] = 4;
	indexList[11] = 6;


	// 上
	vertexList[13].Position.Set( size, size, -size);
	vertexList[12].Position.Set( size, size,  size);
	vertexList[14].Position.Set(-size, size,  size);
	vertexList[15].Position.Set(-size, size,  size);
	vertexList[16].Position.Set(-size, size, -size);
	vertexList[17].Position.Set( size, size, -size);
	indexList[13] = 4;
	indexList[12] = 0;
	indexList[14] = 3;
	indexList[15] = 7;
	indexList[16] = 4;
	indexList[17] = 3;


	// 下
	vertexList[18].Position.Set( size,-size, -size);
	vertexList[19].Position.Set( size,-size,  size);
	vertexList[20].Position.Set(-size,-size,  size);
	vertexList[21].Position.Set(-size,-size,  size);
	vertexList[22].Position.Set(-size,-size, -size);
	vertexList[23].Position.Set( size,-size, -size);
	indexList[18] = 1;
	indexList[19] = 5;
	indexList[20] = 6;
	indexList[21] = 2;
	indexList[22] = 1;
	indexList[23] = 6;


	// 右
	vertexList[24].Position.Set( size,  size,-size);
	vertexList[25].Position.Set( size,  size, size);
	vertexList[26].Position.Set( size, -size, size);
	vertexList[27].Position.Set( size, -size, size);
	vertexList[28].Position.Set( size, -size,-size);
	vertexList[29].Position.Set( size,  size,-size);
	indexList[24] = 3;			 
	indexList[25] = 2;
	indexList[26] = 6;
	indexList[27] = 7;
	indexList[28] = 3;
	indexList[29] = 6;


	// 左
	vertexList[30].Position.Set(-size,  size, -size);
	vertexList[31].Position.Set(-size,  size, size);
	vertexList[32].Position.Set(-size, -size,  size);
	vertexList[33].Position.Set(-size, -size,  size);
	vertexList[34].Position.Set(-size, -size, -size);
	vertexList[35].Position.Set(-size,  size, -size);
	indexList[30] = 4;
	indexList[31] = 5;
	indexList[32] = 1;
	indexList[33] = 0;
	indexList[34] = 4;
	indexList[35] = 1;


	// メッシュセット
	m_vertexDataList.resize(m_vertexNum);
	for (uInt32 i = 0; i < m_vertexNum; i++)
	{
		m_vertexDataList[i] = std::make_shared<SYSTEMS::VertexData>();
		m_vertexDataList[i]->Position = vertexList[i].Position;
		m_vertexDataList[i]->Color.Set(1.0f, 1.0f, 1.0f, 1.0f);
		m_vertexDataList[i]->Normal = m_vertexDataList[i]->Position;
		m_vertexDataList[i]->Texcoord = vertexList[i].Texcoord;

	}

	// インデックス生成
	m_faceList.resize(m_faceNum);
	for (uInt32 i = 0; i < m_faceNum; i++)
	{
		m_faceList[i] = std::make_shared<SYSTEMS::Face>();
		m_faceList[i]->Indices.resize(6);
		for (uInt32 num = 0; num < 6; num++)
		{
			uInt32 index = (i * 6) + num;
			m_faceList[i]->Indices[num] = indexList[index];
		}
	}

}

void GAME_SYSTEMS::Mesh::LoadSphere(Float32 meshSize ,uInt32 devision)
{
	// インデックス生成
	Vector<SYSTEMS::Face> face;
	for (uInt32 y = 0; y < devision; y++)
	{
		for (uInt32 x = 0; x < devision; x++)
		{
			// 左上座標のインデックス
			Int32 count = (devision + 1) * y + x;			

			 SYSTEMS::Face f;
			 f.Indices.resize(3);
			// 上半分
			f.Indices[0] = count;
			f.Indices[1] = count + 1;
			f.Indices[2] = count + 1 + (devision + 1);

			face.emplace_back(f);

			// 下半分
			f.Indices[0] = count;
			f.Indices[1] = count + (devision + 1) + 1;
			f.Indices[2] = count + (devision + 1);

			face.emplace_back(f);
		}
	}

	m_faceNum = static_cast<uInt32>(face.size());
	m_faceList.resize(m_faceNum);
	for (uInt32 num = 0; num < m_faceNum; num++)
	{
		m_faceList[num] = std::make_shared<SYSTEMS::Face>();
		m_faceList[num]->Indices = face[num].Indices;
	}

	// 頂点作成
	Vector<SYSTEMS::VertexData> vertexList;

	// 方位角と仰角から球メッシュの頂点データを作成
	for (uInt32 y = 0; y <= devision; y++)
	{
		// 仰角をセット
		Float32 elevation = (DirectX::XM_PI * (Float32)y) / (Float32)devision;
		
		// 仰角に応じた半径を計算
		Float32 r = meshSize * sinf(elevation);

		for (uInt32 x = 0; x <= devision; x++)
		{
			// 方位角をセット
			Float32 azimuth = (2.0f * DirectX::XM_PI * (Float32)x) / (Float32)devision;	

			SYSTEMS::VertexData v;
			v.Position.x = r * cosf(azimuth);
			v.Position.y = meshSize * cosf(elevation);
			v.Position.z = r * sinf(azimuth);

			// 法線をセット
			v.Normal = myMath::Vector3::Normalize(v.Position);

			// カラー
			v.Color.Set(1.0f, 1.0f, 1.0f, 1.0f);

			vertexList.emplace_back(v);
		}
	}
	m_vertexNum = static_cast<uInt32>(vertexList.size());
	m_vertexDataList.resize(m_vertexNum);
	for (uInt32 num = 0; num < m_vertexNum; num++)
	{
		m_vertexDataList[num] = std::make_shared<SYSTEMS::VertexData>();
		m_vertexDataList[num]->Position = vertexList[num].Position;
		m_vertexDataList[num]->Color = vertexList[num].Color;
		m_vertexDataList[num]->Normal = vertexList[num].Normal;
	}
}

void GAME_SYSTEMS::Mesh::LoadTerrain(Float32 meshSize, uInt32 terrainSizeX, uInt32 terrainSizeY)
{
	// 頂点作成
	Float32 meshDistance = meshSize * 2.0f;
	m_faceNum = terrainSizeX * terrainSizeY;
	m_vertexNum = m_faceNum * 6;
	Vector<SYSTEMS::VertexData> vertexList;
	for (uInt32 y = 0; y < terrainSizeY; y++)
	{
		Float32 meshOffsetY = meshDistance * y;
		for (uInt32 x = 0; x < terrainSizeX; x++)
		{
			Float32 meshOffsetX = meshDistance * x;
			SYSTEMS::VertexData addVertex[6];
			addVertex[0].Position.Set(-meshSize + meshOffsetX, 0.0f,  meshSize + meshOffsetY);
			addVertex[1].Position.Set(-meshSize + meshOffsetX, 0.0f, -meshSize + meshOffsetY);
			addVertex[2].Position.Set( meshSize + meshOffsetX, 0.0f, -meshSize + meshOffsetY);
			addVertex[3].Position.Set( meshSize + meshOffsetX, 0.0f,  meshSize + meshOffsetY);
			addVertex[4].Position.Set(-meshSize + meshOffsetX, 0.0f,  meshSize + meshOffsetY);
			addVertex[5].Position.Set( meshSize + meshOffsetX, 0.0f, -meshSize + meshOffsetY);

			addVertex[0].Texcoord.Set(0.0f,0.0f);
			addVertex[1].Texcoord.Set(0.0f,1.0f);
			addVertex[2].Texcoord.Set(1.0f,1.0f);
			addVertex[3].Texcoord.Set(1.0f,0.0f);
			addVertex[4].Texcoord.Set(0.0f,0.0f);
			addVertex[5].Texcoord.Set(1.0f,1.0f);

			for (uInt32 num = 0; num < 6; num++)
			{
				addVertex[num].Normal = addVertex[num].Position;
				vertexList.emplace_back(addVertex[num]);
			}
		}
	}

	// メッシュセット
	m_vertexDataList.resize(m_vertexNum);
	for (uInt32 i = 0; i < m_vertexNum; i++)
	{
		// 頂点セット
		m_vertexDataList[i] = std::make_shared<SYSTEMS::VertexData>();
		m_vertexDataList[i]->Position = vertexList[i].Position;
		m_vertexDataList[i]->Normal = vertexList[i].Normal;
		m_vertexDataList[i]->Texcoord = vertexList[i].Texcoord;
	}
	// フェースセット
	uInt32 counter = 0;
	m_faceList.resize(m_faceNum);
	for (uInt32 i = 0; i < m_faceNum; i++)
	{
		m_faceList[i] = std::make_shared<SYSTEMS::Face>();
		for (uInt32 j = 0; j < 6; j++)
		{
			m_faceList[i]->Indices.emplace_back(counter);
			counter++;
		}
	}
}

void GAME_SYSTEMS::Mesh::Releace()
{
	m_vertexNum = 0;
	m_vertexDataList.clear();
	m_faceList.clear();
}
