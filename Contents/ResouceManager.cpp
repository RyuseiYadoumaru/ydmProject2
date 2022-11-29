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


void GAME_SYSTEMS::ResourceManager::Releace()
{
	for (auto& model : m_modelDataList)
	{
		model.second->Releace();
	}

}

void GAME_SYSTEMS::ResourceManager::SetUp()
{
	// モデルデータ拡張子
	m_fileDataExtList[FileData::Model].emplace_back("fbx");
	m_fileDataExtList[FileData::Model].emplace_back("obj");
	m_fileDataExtList[FileData::Model].emplace_back("x");

	// オーディオデータ拡張子
	m_fileDataExtList[FileData::Audio].emplace_back("wav");
	m_fileDataExtList[FileData::Audio].emplace_back("mp3");

	// スプライトデータ拡張子
	m_fileDataExtList[FileData::Sprite].emplace_back("png");
	m_fileDataExtList[FileData::Sprite].emplace_back("jpg");
	m_fileDataExtList[FileData::Sprite].emplace_back("tga");
	m_fileDataExtList[FileData::Sprite].emplace_back("bmp");

	// ファイルパスリスト生成

	Vector<Vector<T_String>> filePathList;
	filePathList.emplace_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("*")));
	filePathList.emplace_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/skydome"), TEXT("*")));

	for (auto& filePath : filePathList)
	{
		for (auto& file : filePath)
		{
			m_filePathList[TOOLS::FileSystem::GetFileName(file)] = file;
		}
	}
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
