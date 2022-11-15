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
#include "Timer.h"
#include "../Animation.h"
#include "../AnimationClip.h"
#include "../System/DirectXGraphics.h"

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
	m_animation->SetBlendParameter(0.0f);
	m_animation->UpdateAnimation(Timer::FixDeltaTime());
	m_animation->UpdateConstantBufferBoneMatrix();

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
		int meshindex = node->mMeshes[i];			// �m�[�h��i�Ԗڃ��b�V���̃C���f�b�N�X���擾
		aiMesh* mesh = assimpScene->GetScene()->mMeshes[meshindex];	// �V�[�����烁�b�V���{�̂����o��
		m_meshList.push_back(this->ProcessMesh(mesh, assimpScene, meshindex));
	}

	// �q�m�[�h�ɂ��Ă����
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], assimpScene);
	}
}

GAME_SYSTEMS::Polygon<SkeletalMesh::Vertex> GAME_SYSTEMS::SkeletalMesh::ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx)
{
	std::vector<Vertex> vertices;			// ���_
	std::vector<unsigned int> indices;		// �ʂ̍\�����
	//std::vector<Texture> textures;			// �e�N�X�`��

	// ���_�����擾
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.m_Pos.x = mesh->mVertices[i].x;
		vertex.m_Pos.y = mesh->mVertices[i].y;
		vertex.m_Pos.z = mesh->mVertices[i].z;

		// �@���x�N�g�������݂��邩�H
		if (mesh->HasNormals()) {
			vertex.m_Normal.x = mesh->mNormals[i].x;
			vertex.m_Normal.y = mesh->mNormals[i].y;
			vertex.m_Normal.z = mesh->mNormals[i].z;
		}
		else {
			vertex.m_Normal.x = 0.0f;
			vertex.m_Normal.y = 0.0f;
			vertex.m_Normal.z = 0.0f;
		}

		// �e�N�X�`�����W�i�O�Ԗځj�����݂��邩�H
		if (mesh->HasTextureCoords(0)) {
			vertex.m_Tex.x = mesh->mTextureCoords[0][i].x;
			vertex.m_Tex.y = mesh->mTextureCoords[0][i].y;
		}

		vertex.m_BoneNum = 0;

		for (unsigned int b = 0; b < 4; b++)
		{
			vertex.m_BoneIndex[b] = -1;
			vertex.m_BoneWeight[b] = 0.0f;
		}

		vertices.push_back(vertex);
	}

	//�{�[���f�[�^������
	for (unsigned int b = 0; b < mesh->mNumBones; b++)
	{
		// ���b�V���Ɋ֘A�Â��Ă�{�[�������擾
		aiBone* bone = mesh->mBones[b];

		// �{�[���Ɋ֘A�Â��Ă��钸�_��I�Ѥ�E�F�C�g�l���Z�b�g����
		for (unsigned int widx = 0; widx < bone->mNumWeights; widx++)
		{
			aiVertexWeight weight = bone->mWeights[widx];

			unsigned int vidx = weight.mVertexId;			// ���̃E�G�C�g�Ɋ֘A�Â��Ă钸�_idx

			// ���b�V���̒��̉��Ԗڂ�
			vertices[vidx].m_BoneWeight[vertices[vidx].m_BoneNum] = weight.mWeight;

			// �Y������{�[�����̃C���f�b�N�X�l���Z�b�g
			vertices[vidx].m_BoneIndex[vertices[vidx].m_BoneNum] = assimpScene
				->GetBoneIndexByName(bone->mName.C_Str());

			vertices[vidx].m_BoneNum++;

			assert(vertices[vidx].m_BoneNum <= 4);
		}
	}

	//// �e�N�X�`�������擾����
	//if (mesh->mMaterialIndex >= 0)
	//{
	//	// ���̃��b�V���̃}�e���A���C���f�b�N�X�l���擾����
	//	int	mtrlidx = mesh->mMaterialIndex;

	//	// �V�[������}�e���A���f�[�^���擾����
	//	aiMaterial* material = scene->mMaterials[mtrlidx];

	//	// ���̃}�e���A���Ɋ֘A�Â����e�N�X�`�������o��
	//	std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);

	//	// ���̃��b�V���Ŏg�p���Ă���e�N�X�`����ۑ�
	//	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//}

	// �ʂ̍\�������擾
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	return Polygon(vertices, indices);
}