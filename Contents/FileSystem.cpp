//*****************************************************************************
//* @file   FileSystem.cpp
//* @brief  ファイルシステム
//* @note   ファイルの便利関数をまとめる
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "FileSystem.h"


T_String tools::FileSystem::GetFileName(T_StringView filePath, bool isExt) noexcept
{
    T_String fileName;
    uInt32 index = filePath.find_last_of(m_slash);
    uInt32 dotIndex = filePath.find_last_of(m_dot);
    
    /** 拡張子あり */
    if(isExt == true) fileName = filePath.substr(index + 1);
    
    /** 拡張子なし */
    else
    {
        uInt32 nameLength = dotIndex - (index + 1);
        fileName = filePath.substr(index + 1, nameLength);
    }

    return fileName;
}



T_String tools::FileSystem::GetFileExt(T_StringView filePath) noexcept
{
    T_String extName;
    uInt32 dotIndex = filePath.find_last_of(m_dot);

    /** 拡張子を抽出する */
    extName = filePath.substr(dotIndex + 1, filePath.size() - dotIndex);
    return extName;
}



data::Type tools::FileSystem::JudgeFolderOrFile(T_StringView dataName) noexcept
{
    uInt32 index = 0;
    index = dataName.find(m_dot);
    if (index != -1) return data::Type::File;
    return data::Type::Folder;
}



Vector<T_String> tools::FileSystem::GetAllFileFromFolder(T_StringView folderPath, T_StringView extName)
{
    Vector<T_String> filePathList;

    HANDLE hFind;
    WIN32_FIND_DATA win32fd;

    /** 探索用仮パス */
    T_String path;
    T_String ext;
    path = folderPath;
    ext= extName;
    T_String searchPath = path + TEXT("*.") + ext;

    /*
     * 探索開始
     * フォルダ内にデータがない時はAssertで無理やり止める.
    */ 
    hFind = FindFirstFile(searchPath.c_str(), &win32fd);
    

    /** 探索 */
    do
    {
        if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {}

        else
        {
            filePathList.push_back(path + win32fd.cFileName);
        }

    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return filePathList;
}




T_String tools::FileSystem::GetDirectryPathFromFilePath(T_StringView filePath)
{
    T_String directryPath;
    /** 最後のスラッシュのインデックスを保存 */
    uInt32 index =  filePath.find_last_of(m_slash);
    directryPath = filePath.substr(0, index + 1);
    return directryPath;
}
