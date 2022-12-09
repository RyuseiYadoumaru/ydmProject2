//*****************************************************************************
//* @file   ResourceManager.cpp
//* @brief  
//* @note   メッシュのリソースを管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "ResourceManager.h"
#include "ModelData.h"
#include "Model.h"
#include "Texture.h"
#include "AnimationClip.h"
#include "FileSystem.h"
#include "../System/MessageWindow.h"

USING_GAME_SYSTEMS;

SharedPtr<ModelData> GAME_SYSTEMS::ResourceManager::GetModelData(T_String fileName)
{
	if (m_modelDataList.contains(fileName) == true)
	{
		return m_modelDataList[fileName];
	}
	else
	{
		auto ext = TOOLS::FileSystem::GetFileExt(fileName);
		if (CheckExt(ext, FileData::Model) == true )
		{
			m_modelDataList[fileName] = std::make_shared<ModelData>();
			m_modelDataList[fileName]->Load(GetFilePath(fileName));
		}
	}
	return m_modelDataList[fileName];
}

SharedPtr<Texture> GAME_SYSTEMS::ResourceManager::GetTexture(T_String fileName)
{
	if (m_textureList.contains(fileName) == true)
	{
		return m_textureList[fileName];
	}
	else
	{
		auto ext = TOOLS::FileSystem::GetFileExt(fileName);
		if (CheckExt(ext, FileData::Sprite) == true)
		{
			m_textureList[fileName] = std::make_shared<Texture>();
			m_textureList[fileName]->Load(GetFilePath(fileName));
		}
	}
	return m_textureList[fileName];
}

SharedPtr<AnimationClip> GAME_SYSTEMS::ResourceManager::GetAnimationClip(T_String fileName)
{
	if (m_animationList.contains(fileName) == true)
	{
		return m_animationList[fileName];
	}
	else
	{
		auto ext = TOOLS::FileSystem::GetFileExt(fileName);
		if (CheckExt(ext, FileData::Animation) == true)
		{
			m_animationList[fileName] = std::make_shared<AnimationClip>();
			bool sts =  m_animationList[fileName]->Load(GetFilePath(fileName));
			if (sts == false)
			{
				m_animationList[fileName]->Releace();
				m_animationList.erase(fileName);
				return nullptr;
			}
		}
	}
	return m_animationList[fileName];
}


void GAME_SYSTEMS::ResourceManager::Releace()
{
	for (auto& model : m_modelDataList)
	{
		model.second->Releace();
	}

}

void GAME_SYSTEMS::ResourceManager::SetUp()
{
	// アニメーションデータ拡張子
	m_fileDataExtList[FileData::Animation].emplace_back("fbx");
	m_fileDataExtList[FileData::Animation].emplace_back("FBX");
	m_fileDataExtList[FileData::Animation].emplace_back("x");

	// オーディオデータ拡張子
	m_fileDataExtList[FileData::Audio].emplace_back("wav");
	m_fileDataExtList[FileData::Audio].emplace_back("mp3");

	// モデルデータ拡張子
	m_fileDataExtList[FileData::Model].emplace_back("fbx");
	m_fileDataExtList[FileData::Model].emplace_back("FBX");
	m_fileDataExtList[FileData::Model].emplace_back("obj");
	m_fileDataExtList[FileData::Model].emplace_back("x");

	// スプライトデータ拡張子
	m_fileDataExtList[FileData::Sprite].emplace_back("png");
	m_fileDataExtList[FileData::Sprite].emplace_back("jpg");
	m_fileDataExtList[FileData::Sprite].emplace_back("tga");
	m_fileDataExtList[FileData::Sprite].emplace_back("bmp");

	// ファイルパスリスト生成
	Vector<Vector<T_String>> filePathList;
	filePathList.emplace_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("*")));
	filePathList.emplace_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/skydome/"), TEXT("*")));
	filePathList.emplace_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/Human/"), TEXT("*")));
	filePathList.emplace_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/ThirdPerson/"), TEXT("*")));

	for (auto& filePath : filePathList)
	{
		for (auto& file : filePath)
		{
			m_filePathList[TOOLS::FileSystem::GetFileName(file)] = file;
		}
	}

	// ジオメトリ生成
	m_geometryList[GeometryType::Terrain] = std::make_shared<Model>(nullptr);
	m_geometryList[GeometryType::Terrain]->LoadGeometry(Model::Geometry::Terrain);
	m_geometryList[GeometryType::Cube] = std::make_shared<Model>(nullptr);
	m_geometryList[GeometryType::Cube]->LoadGeometry(Model::Geometry::Cube);
	m_geometryList[GeometryType::Sphare] = std::make_shared<Model>(nullptr);
	m_geometryList[GeometryType::Sphare]->LoadGeometry(Model::Geometry::Sphare);
}

void GAME_SYSTEMS::ResourceManager::ShutDown()
{
	m_filePathList.clear();
	m_fileDataExtList.clear();
	for (auto& model : m_modelDataList)
	{
		model.second->Releace();
	}
	m_modelDataList.clear();

	for (auto& model : m_geometryList)
	{
		model.second->Releace();
	}
}

bool GAME_SYSTEMS::ResourceManager::CheckExt(T_String ext, ResourceManager::FileData data)
{
	for (const auto& e : m_fileDataExtList[data])
	{
		if (ext == e)
		{
			return true;
		}
	}
	return false;
}

T_String GAME_SYSTEMS::ResourceManager::GetFilePath(T_String fileName)
{
	if (m_filePathList.contains(fileName) == false)
	{
		SYSTEMS::MessageWindow::GetInstance()->Error("データが見つかりません");
		return "Nodata";
	}
	return m_filePathList[fileName];
}
