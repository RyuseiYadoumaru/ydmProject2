#include "MeshManager.h"
#include "StaticMesh.h"
#include "DefaultStaticMesh.h"
#include "SkeletalMesh.h"
#include "AnimationClip.h"
#include "FileSystem.h"
#include "../System/MessageWindow.h"

USING_GAME_SYSTEMS;

SharedPtr<StaticMesh> GAME_SYSTEMS::MeshManager::GetStaticMesh(T_String fileName)
{
	if (m_staticMeshList.contains(fileName) == true)
	{
		return m_staticMeshList[fileName];
	}
	else
	{
		if (TOOLS::FileSystem::GetFileExt(fileName) == "x" ||
			TOOLS::FileSystem::GetFileExt(fileName) == "obj")
		{
			m_staticMeshList[fileName] = std::make_shared<StaticMesh>();
			m_staticMeshList[fileName]->Load(GetFilePath(fileName));
		}
	}
	return m_staticMeshList[fileName];
}

SharedPtr<SkeletalMesh> GAME_SYSTEMS::MeshManager::GetSkeletalMesh(T_String fileName)
{
	if (m_skeletalMeshList.contains(fileName) == true)
	{
		return m_skeletalMeshList[fileName];
	}
	else
	{
		if (TOOLS::FileSystem::GetFileExt(fileName) == "fbx" ||
			TOOLS::FileSystem::GetFileExt(fileName) == "x")
		{
			m_skeletalMeshList[fileName] = std::make_shared<SkeletalMesh>();
			m_skeletalMeshList[fileName]->Load(GetFilePath(fileName));
		}
	}
	return m_skeletalMeshList[fileName];
}

SharedPtr<AnimationClip> GAME_SYSTEMS::MeshManager::GetAnimationClip(T_String fileName)
{
	if (m_skeletalMeshList.contains(fileName) == true)
	{
		return m_skeletalMeshList[fileName]->GetAnimationClip();
	}

	if (TOOLS::FileSystem::GetFileExt(fileName) == "fbx" || TOOLS::FileSystem::GetFileExt(fileName) == "FBX")
	{
		m_skeletalMeshList[fileName] = std::make_shared<SkeletalMesh>();
		m_skeletalMeshList[fileName]->Load(GetFilePath(fileName));
		return m_skeletalMeshList[fileName]->GetAnimationClip();
	}
	return nullptr;
}

void GAME_SYSTEMS::MeshManager::Releace()
{
	for (auto& mesh : m_staticMeshList)
	{
		mesh.second->Releace();
	}

	for (auto& mesh : m_skeletalMeshList)
	{
		mesh.second->Releace();
	}

	m_staticMeshList[TERRAIN] = std::make_shared<DefaultStaticMesh>();
	m_staticMeshList[TERRAIN]->Load(TERRAIN);

	m_staticMeshList[SPHERE] = std::make_shared<DefaultStaticMesh>();
	m_staticMeshList[SPHERE]->Load(SPHERE);

}

void GAME_SYSTEMS::MeshManager::SetUp()
{
	Vector<Vector<T_String>> filePathList;
	auto add = TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("fbx"));
	filePathList.push_back(add);
	add.clear();
	add = TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("x"));
	filePathList.push_back(add);
	add = TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("obj"));
	filePathList.push_back(add);

	for (auto& filePath : filePathList)
	{
		for (auto& file : filePath)
		{
			m_filePathList[TOOLS::FileSystem::GetFileName(file)] = file;
		}
	}

	m_staticMeshList[TERRAIN] = std::make_shared<DefaultStaticMesh>();
	m_staticMeshList[TERRAIN]->Load(TERRAIN);

	m_staticMeshList[SPHERE] = std::make_shared<DefaultStaticMesh>();
	m_staticMeshList[SPHERE]->Load(SPHERE);

}

void GAME_SYSTEMS::MeshManager::ShutDown()
{
	m_filePathList.clear();
	m_skeletalMeshList.clear();
	m_staticMeshList.clear();
}

T_String GAME_SYSTEMS::MeshManager::GetFilePath(T_String fileName)
{
	if (m_filePathList.contains(fileName) == false)
	{
		SYSTEMS::MessageWindow::GetInstance()->Error("メッシュデータが見つかりません");
		return "Nodata";
	}

	return m_filePathList[fileName];
}
