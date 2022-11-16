#include "StaticMesh.h"
#include "Material.h"
#include "../System/DirectXGraphics.h"
#include <assimp/scene.h>

USING_GAME_SYSTEMS;

void GAME_SYSTEMS::StaticMesh::Load(T_String meshName)
{
	m_assimpScene.Init(meshName);
	// ���b�V���f�[�^�쐬
	aiNode* rootNode = m_assimpScene.GetScene()->mRootNode;
	ProcessNode(rootNode, &m_assimpScene);

	// �f�t�H���g�̃}�e���A���쐬
	m_material = std::make_shared<Material>();
	m_material->LoadShader(TEXT("DefaultMeshVertexShader"), TEXT("UnlitDefaultPixelShader"));

	m_assimpScene.Exit();
}

void GAME_SYSTEMS::StaticMesh::Releace()
{
	for (auto& polygon : m_meshList)
	{
		polygon.Uninit();
	}
	m_meshList.clear();
}

void GAME_SYSTEMS::StaticMesh::Render()
{
	ID3D11DeviceContext& devcon = systems::DirectXGraphics::GetInstance()->GetImmediateContext();
	for (auto& polygon : m_meshList)
	{
		polygon.Draw(&devcon);
	}
}

void GAME_SYSTEMS::StaticMesh::LoadMaterial()
{
	m_material = std::make_shared <Material>();
	// �}�e���A�������݂��邩�H
	if (m_assimpScene.GetScene()->HasMaterials())
	{
		// �}�e���A���� �擾
		int nummaterial = m_assimpScene.GetScene()->mNumMaterials;

		for (int i = 0; i < nummaterial; i++)
		{
			Material mtrl;

			// i�Ԗڂ̃}�e���A�����擾
			aiMaterial* mat = m_assimpScene.GetScene()->mMaterials[i];

			aiColor3D colordiffuse(1.f, 1.f, 1.f);
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, colordiffuse);
			
			m_material->SetDiffuseColor(
				colordiffuse.r,
				colordiffuse.g,
				colordiffuse.b,
				1.0f);

			aiColor3D colorspecular(0.f, 0.f, 0.f);
			mat->Get(AI_MATKEY_COLOR_SPECULAR, colorspecular);
			m_material->SetSpecularColor(
				colorspecular.r,
				colorspecular.g,
				colorspecular.b,
				1.0f);

			aiColor3D colorambient(0.f, 0.f, 0.f);
			mat->Get(AI_MATKEY_COLOR_AMBIENT, colorambient);
			m_material->SetAmbientColor(
				colorambient.r,
				colorambient.g,
				colorambient.b,
				1.0f);


			aiColor3D coloremissive(0.f, 0.f, 0.f);
			mat->Get(AI_MATKEY_COLOR_EMISSIVE, coloremissive);

			//mtrl.m_Emissive.x = coloremissive.r;
			//mtrl.m_Emissive.y = coloremissive.g;
			//mtrl.m_Emissive.z = coloremissive.b;

			//float power;
			//mat->Get(AI_MATKEY_SHININESS_STRENGTH, power);
			//mtrl.m_SpecularPower = power;

			//m_materials.push_back(mtrl);
		}
	}
}


void GAME_SYSTEMS::StaticMesh::ProcessNode(aiNode* node, AssimpScene* assimpScene)
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

GAME_SYSTEMS::Polygon<StaticMesh::Vertex> GAME_SYSTEMS::StaticMesh::ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx)
{
	Vector<StaticMesh::Vertex> vertexList;	// ���_
	Vector<uInt32> indexList;		// �ʂ̍\�����
	//Vector<Texture> textures;	// �e�N�X�`��
	//Material material;			//�}�e���A��

	// ���_�����擾
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		StaticMesh::Vertex vertex;

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;

		// �@���x�N�g�������݂��邩�H
		if (mesh->HasNormals())
		{
			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;
		}
		else
		{
			vertex.Normal.x = 0.0f;
			vertex.Normal.y = 0.0f;
			vertex.Normal.z = 0.0f;
		}

		// �e�N�X�`�����W�i�O�Ԗځj�����݂��邩�H
		if (mesh->HasTextureCoords(0))
		{
			vertex.Texcoord.x = mesh->mTextureCoords[0][i].x;
			vertex.Texcoord.y = mesh->mTextureCoords[0][i].y;
		}
		vertexList.push_back(vertex);
	}

	// �e�N�X�`�������擾����
	//if (mesh->mMaterialIndex >= 0)
	//{
	//	// ���̃��b�V���̃}�e���A���C���f�b�N�X�l���擾����
	//	int	mtrlidx = mesh->mMaterialIndex;

	//	// ���̃��b�V���̃}�e���A�����擾����
	//	material = m_materials[mtrlidx];

	//	// �V�[������}�e���A���f�[�^���擾����
	//	aiMaterial* material = scene->mMaterials[mtrlidx];

	//	// ���̃}�e���A���Ɋ֘A�Â����e�N�X�`�������o��
	//	std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);

	//	// ���̃��b�V���Ŏg�p���Ă���e�N�X�`����ۑ�
	//	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//}

	// �ʂ̍\�������擾
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indexList.push_back(face.mIndices[j]);
		}
	}
	return Polygon<StaticMesh::Vertex>(vertexList,indexList);
}
