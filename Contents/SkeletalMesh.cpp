//*****************************************************************************
//* @file   SkeletalMesh.cpp
//* @brief  �X�P���^�����b�V��
//* @note   �{�[�������������Ă��郁�b�V���N���X
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "SkeletalMesh.h"
#include "Skeleton.h"
#include "AnimationClip.h"
#include "Timer.h"
#include "Matrix4x4.h"
#include "../Animation.h"
#include "../System/DirectXGraphics.h"
#include "../System/DX11SetBoneMatrix.h"

#include <assimp/scene.h>

USING_GAME_SYSTEMS;

void GAME_SYSTEMS::SkeletalMesh::Load(T_String meshName)
{
	m_assimpScene.Init(meshName);

	// ���b�V���f�[�^�쐬
	aiNode* rootNode = m_assimpScene.GetScene()->mRootNode;
	ProcessNode(rootNode, &m_assimpScene);

	// �{�[���f�[�^�쐬
	m_skeleton = std::make_shared<Skeleton>();
	m_animation = std::make_shared<Animation>();
	m_skeleton->Load(&m_assimpScene);
	m_animation->SetSkeleton(m_skeleton.get());

	m_assimpScene.Exit();
}

void GAME_SYSTEMS::SkeletalMesh::Releace()
{
	for (auto& polygon : m_meshList)
	{
		polygon.Uninit();
	}
	if (m_animation != nullptr)
	{
		m_animation = nullptr;
	}
	if (m_skeleton != nullptr)
	{
		m_skeleton = nullptr;
	}
}

void GAME_SYSTEMS::SkeletalMesh::Render()
{
	// �A�j���[�V�����X�V
	//m_animation->SetBlendParameter(0.0f);
	m_animation->UpdateAnimation(0.0f);
	//m_animation->UpdateConstantBufferBoneMatrix();

	// �{�[���s�񐶐�
	Vector<DirectX::XMFLOAT4X4> skeletonMatrixList;
	for (auto& mtx : m_skeleton->GetBonesMatrix())
	{
		skeletonMatrixList.emplace_back(mtx);
	}
	systems::DX11SetBoneMatrix::GetInstance()->SetConstantBuffer(skeletonMatrixList);
	
	// ���b�V���`��
	ID3D11DeviceContext& devcon = systems::DirectXGraphics::GetInstance()->GetImmediateContext();
	for (auto& polygon : m_meshList)
	{
		polygon.Draw(&devcon);
	}
}

void GAME_SYSTEMS::SkeletalMesh::SetAnimationClip(T_String animDataName)
{
	m_assimpScene.Init(animDataName);

	// �A�j���[�V�����f�[�^�쐬
	SharedPtr<AnimationClip> animClip = std::make_shared<AnimationClip>();
	animClip->Load(&m_assimpScene, 0);
	m_animation->AddAnimationClips(animClip.get());
	m_animationClipList.emplace_back(std::move(animClip));
	m_assimpScene.Exit();
}

void GAME_SYSTEMS::SkeletalMesh::ProcessNode(aiNode* node, AssimpScene* assimpScene)
{
	// �m�[�h���̃��b�V���̐������[�v����
	for (uInt32 i = 0; i < node->mNumMeshes; i++)
	{
		// �m�[�h��i�Ԗڃ��b�V���̃C���f�b�N�X���擾
		Int32 meshindex = node->mMeshes[i];			
		
		// �V�[�����烁�b�V���{�̂����o��
		aiMesh* mesh = assimpScene->GetScene()->mMeshes[meshindex];
		m_meshList.push_back(this->ProcessMesh(mesh, assimpScene, meshindex));
	}

	// �q�m�[�h�ɂ��Ă����
	for (uInt32 i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], assimpScene);
	}
}

GAME_SYSTEMS::Polygon<SkeletalMesh::Vertex> GAME_SYSTEMS::SkeletalMesh::ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx)
{
	std::vector<Vertex> vertices;			// ���_
	std::vector<uInt32> indices;		// �ʂ̍\�����

	// ���_�����擾
	for (uInt32 i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.m_Pos.x = mesh->mVertices[i].x;
		vertex.m_Pos.y = mesh->mVertices[i].y;
		vertex.m_Pos.z = mesh->mVertices[i].z;

		// �@���x�N�g�������݂��邩�H
		if (mesh->HasNormals()) 
		{
			vertex.m_Normal.x = mesh->mNormals[i].x;
			vertex.m_Normal.y = mesh->mNormals[i].y;
			vertex.m_Normal.z = mesh->mNormals[i].z;
		}

		// �e�N�X�`�����W�i�O�Ԗځj�����݂��邩�H
		if (mesh->HasTextureCoords(0)) 
		{
			vertex.m_Tex.x = mesh->mTextureCoords[0][i].x;
			vertex.m_Tex.y = mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(vertex);
	}

	//�{�[���f�[�^������
	for (uInt32 b = 0; b < mesh->mNumBones; b++)
	{
		// ���b�V���Ɋ֘A�Â��Ă�{�[�������擾
		aiBone* bone = mesh->mBones[b];

		// �{�[���Ɋ֘A�Â��Ă��钸�_��I�Ѥ�E�F�C�g�l���Z�b�g����
		for (uInt32 widx = 0; widx < bone->mNumWeights; widx++)
		{
			aiVertexWeight weight = bone->mWeights[widx];

			unsigned int vidx = weight.mVertexId;			// ���̃E�G�C�g�Ɋ֘A�Â��Ă钸�_idx

			// ���b�V���̒��̉��Ԗڂ�
			vertices[vidx].m_BoneWeight[vertices[vidx].m_BoneNum] = weight.mWeight;

			// �Y������{�[�����̃C���f�b�N�X�l���Z�b�g
			vertices[vidx].m_BoneIndex[vertices[vidx].m_BoneNum] = assimpScene->GetBoneIndexByName(bone->mName.C_Str());

			vertices[vidx].m_BoneNum++;

			assert(vertices[vidx].m_BoneNum <= 4);
		}
	}

	// �ʂ̍\�������擾
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