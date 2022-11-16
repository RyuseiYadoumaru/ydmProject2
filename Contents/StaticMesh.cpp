#include "StaticMesh.h"
#include "Material.h"
#include "../System/DirectXGraphics.h"
#include <assimp/scene.h>

USING_GAME_SYSTEMS;

void GAME_SYSTEMS::StaticMesh::Load(T_String meshName)
{
	m_assimpScene.Init(meshName);
	// メッシュデータ作成
	aiNode* rootNode = m_assimpScene.GetScene()->mRootNode;
	ProcessNode(rootNode, &m_assimpScene);

	// デフォルトのマテリアル作成
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
	// マテリアルが存在するか？
	if (m_assimpScene.GetScene()->HasMaterials())
	{
		// マテリアル数 取得
		int nummaterial = m_assimpScene.GetScene()->mNumMaterials;

		for (int i = 0; i < nummaterial; i++)
		{
			Material mtrl;

			// i番目のマテリアルを取得
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
	// ノード内のメッシュの数分ループする
	for (uInt32 i = 0; i < node->mNumMeshes; i++)
	{
		int meshindex = node->mMeshes[i];			// ノードのi番目メッシュのインデックスを取得
		aiMesh* mesh = assimpScene->GetScene()->mMeshes[meshindex];	// シーンからメッシュ本体を取り出す
		m_meshList.push_back(this->ProcessMesh(mesh, assimpScene, meshindex));
	}

	// 子ノードについても解析
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], assimpScene);
	}
}

GAME_SYSTEMS::Polygon<StaticMesh::Vertex> GAME_SYSTEMS::StaticMesh::ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx)
{
	Vector<StaticMesh::Vertex> vertexList;	// 頂点
	Vector<uInt32> indexList;		// 面の構成情報
	//Vector<Texture> textures;	// テクスチャ
	//Material material;			//マテリアル

	// 頂点情報を取得
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		StaticMesh::Vertex vertex;

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;

		// 法線ベクトルが存在するか？
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

		// テクスチャ座標（０番目）が存在するか？
		if (mesh->HasTextureCoords(0))
		{
			vertex.Texcoord.x = mesh->mTextureCoords[0][i].x;
			vertex.Texcoord.y = mesh->mTextureCoords[0][i].y;
		}
		vertexList.push_back(vertex);
	}

	// テクスチャ情報を取得する
	//if (mesh->mMaterialIndex >= 0)
	//{
	//	// このメッシュのマテリアルインデックス値を取得する
	//	int	mtrlidx = mesh->mMaterialIndex;

	//	// このメッシュのマテリアルを取得する
	//	material = m_materials[mtrlidx];

	//	// シーンからマテリアルデータを取得する
	//	aiMaterial* material = scene->mMaterials[mtrlidx];

	//	// このマテリアルに関連づいたテクスチャを取り出す
	//	std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);

	//	// このメッシュで使用しているテクスチャを保存
	//	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//}

	// 面の構成情報を取得
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indexList.push_back(face.mIndices[j]);
		}
	}
	return Polygon<StaticMesh::Vertex>(vertexList,indexList);
}
