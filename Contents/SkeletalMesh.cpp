//*****************************************************************************
//* @file   SkeletalMesh.cpp
//* @brief  スケルタルメッシュ
//* @note   ボーン情報を所持しているメッシュクラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "SkeletalMesh.h"
#include "Skeleton.h"
#include "AnimationClip.h"
#include "Timer.h"
#include "FileSystem.h"
#include "Matrix4x4.h"
#include "../System/DirectXGraphics.h"
#include "../System/DX11SetBoneMatrix.h"

#include <assimp/scene.h>

USING_GAME_SYSTEMS;

void GAME_SYSTEMS::SkeletalMesh::Load(T_String meshName)
{
	m_assimpScene.Init(meshName);

	// メッシュデータ作成
	aiNode* rootNode = m_assimpScene.GetScene()->mRootNode;
	ProcessNode(rootNode, &m_assimpScene);

	// ボーンデータ作成
	m_skeleton = std::make_shared<Skeleton>();
	m_skeleton->Load(&m_assimpScene);

	// アニメーションデータ作成
	if (m_assimpScene.HasAnimation() == true)
	{
		m_animationClip = std::make_shared<AnimationClip>();
		m_animationClip->Load(&m_assimpScene);
		auto name = TOOLS::FileSystem::GetFileName(meshName);
		m_animClipList[name] = m_animationClip;
		// デフォルトボーン行列作成
		Vector<MY_MATH::Matrix4x4> animMtxList;
		m_animationClip->CalcAnimationMatrix(animMtxList, m_skeleton->GetBoneNum());
		m_skeleton->CreateAnimationMatrix(animMtxList);
	}

	m_skeleton->InitDefaultMatrix();
	m_assimpScene.Exit();
}

void GAME_SYSTEMS::SkeletalMesh::Releace()
{
	for (auto& polygon : m_meshList)
	{
		polygon.Uninit();
	}
	if (m_animationClip != nullptr)
	{
		m_animationClip = nullptr;
	}
	if (m_skeleton != nullptr)
	{
		m_skeleton = nullptr;
	}
	m_animClipList.clear();
}

void GAME_SYSTEMS::SkeletalMesh::Render()
{
	// ボーン行列生成
	Vector<DirectX::XMFLOAT4X4> skeletonMatrixList;
	for (auto& mtx : m_skeleton->GetBonesMatrix())
	{
		skeletonMatrixList.emplace_back(mtx);
	}
	systems::DX11SetBoneMatrix::GetInstance()->SetConstantBuffer(skeletonMatrixList);
	
	// メッシュ描画
	ID3D11DeviceContext& devcon = systems::DirectXGraphics::GetInstance()->GetImmediateContext();
	for (auto& polygon : m_meshList)
	{
		polygon.Draw(&devcon);
	}
}

void GAME_SYSTEMS::SkeletalMesh::AddAnimationClip(T_String filePath)
{
	auto name = TOOLS::FileSystem::GetFileName(filePath);
	if (m_animClipList.contains(name) == false)
	{
		m_assimpScene.Init(filePath);
		m_animClipList[name] = std::make_shared<AnimationClip>();
		m_animClipList[name]->Load(&m_assimpScene);
		m_assimpScene.Exit();
	}
}

SkeletalMesh& GAME_SYSTEMS::SkeletalMesh::operator=(const SkeletalMesh& skeletal) noexcept
{
	m_meshList = skeletal.m_meshList;
	m_animationClip = skeletal.m_animationClip;
	m_skeleton = skeletal.m_skeleton;
	m_animClipList = skeletal.m_animClipList;
	return *this;
}

void GAME_SYSTEMS::SkeletalMesh::ProcessNode(aiNode* node, AssimpScene* assimpScene)
{
	// ノード内のメッシュの数分ループする
	for (uInt32 i = 0; i < node->mNumMeshes; i++)
	{
		// ノードのi番目メッシュのインデックスを取得
		Int32 meshindex = node->mMeshes[i];			
		
		// シーンからメッシュ本体を取り出す
		aiMesh* mesh = assimpScene->GetScene()->mMeshes[meshindex];
		m_meshList.push_back(this->ProcessMesh(mesh, assimpScene, meshindex));
	}

	// 子ノードについても解析
	for (uInt32 i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], assimpScene);
	}
}

GAME_SYSTEMS::Polygon<SkeletalMesh::Vertex> GAME_SYSTEMS::SkeletalMesh::ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx)
{
	Vector<Vertex> vertices;	// 頂点
	Vector<uInt32> indices;		// 面の構成情報

	// 頂点情報を取得
	for (uInt32 i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.m_Pos.x = mesh->mVertices[i].x;
		vertex.m_Pos.y = mesh->mVertices[i].y;
		vertex.m_Pos.z = mesh->mVertices[i].z;

		// 法線ベクトルが存在するか？
		if (mesh->HasNormals()) 
		{
			vertex.m_Normal.x = mesh->mNormals[i].x;
			vertex.m_Normal.y = mesh->mNormals[i].y;
			vertex.m_Normal.z = mesh->mNormals[i].z;
		}

		// テクスチャ座標（0番目）が存在するか？
		if (mesh->HasTextureCoords(0)) 
		{
			vertex.m_Tex.x = mesh->mTextureCoords[0][i].x;
			vertex.m_Tex.y = mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(vertex);
	}

	//ボーンデータ初期化
	for (uInt32 b = 0; b < mesh->mNumBones; b++)
	{
		// メッシュに関連づいてるボーン情報を取得
		aiBone* bone = mesh->mBones[b];

		// ボーンに関連づいている頂点を選び､ウェイト値をセットする
		for (uInt32 widx = 0; widx < bone->mNumWeights; widx++)
		{
			aiVertexWeight weight = bone->mWeights[widx];
			
			// このウエイトに関連づいてる頂点idx
			uInt32 vidx = weight.mVertexId;			

			// メッシュの中の何番目か
			vertices[vidx].m_BoneWeight[vertices[vidx].m_BoneNum] = weight.mWeight;

			// 該当するボーン名のインデックス値をセット
			vertices[vidx].m_BoneIndex[vertices[vidx].m_BoneNum] = assimpScene->GetBoneIndexByName(bone->mName.C_Str());

			vertices[vidx].m_BoneNum++;

			assert(vertices[vidx].m_BoneNum <= 4);
		}
	}

	// 面の構成情報を取得
	for (uInt32 i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uInt32 j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return Polygon(vertices, indices);
}