#include	<assimp/cimport.h>
#include	<assimp\postprocess.h>
#include	<assimp/cimport.h>
#include	<assimp/scene.h>
#include	<assimp/mesh.h>

#include	"Assimpscene.h"

bool AssimpScene::Init(T_String filename) {

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

// 終了処理
void AssimpScene::Exit() {
	aiReleaseImport(m_Scene);
}

// シーン取得
const aiScene* AssimpScene::GetScene() const {
	return m_Scene;
}


// アニメーションを持っているか
bool AssimpScene::HasAnimation() {
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