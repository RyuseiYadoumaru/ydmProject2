#include "TextureManager.h"
#include "Texture.h"
#include "FileSystem.h"
#include "../System/MessageWindow.h"


USING_GAME_SYSTEMS;

SharedPtr<Texture> GAME_SYSTEMS::TextureManager::GetTexture(T_String name)
{
    if (m_textureList.contains(name) == true)
    {
        return m_textureList[name];
    }
    else
    {
        m_textureList[name] = std::make_shared<Texture>();
        m_textureList[name]->Load(GetFilePath(name));
    }
    return m_textureList[name];
}

void GAME_SYSTEMS::TextureManager::Releace()
{
    for (auto& tex : m_textureList)
    {
        tex.second->Releace();
    }
}

void GAME_SYSTEMS::TextureManager::SetUp()
{
    Vector<Vector<T_String>> filePathList;
    filePathList.push_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("png")));
    filePathList.push_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("tga")));
    filePathList.push_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("jpg")));
    filePathList.push_back(TOOLS::FileSystem::GetAllFileFromFolder(TEXT("Assets/"), TEXT("bmp")));

    for (auto& filePath : filePathList)
    {
        for (auto& file : filePath)
        {
            m_filePathList[TOOLS::FileSystem::GetFileName(file)] = file;
        }
    }
}

void GAME_SYSTEMS::TextureManager::ShutDown()
{
    m_filePathList.clear();
    m_textureList.clear();
}

T_String GAME_SYSTEMS::TextureManager::GetFilePath(T_String fileName)
{
    if (m_filePathList.contains(fileName) == false)
    {
        SYSTEMS::MessageWindow::GetInstance()->Error("テクスチャデータが見つかりません");
        return "Nodata";
    }

    return m_filePathList[fileName];
}
