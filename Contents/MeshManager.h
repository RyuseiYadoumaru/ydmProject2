//*****************************************************************************
//* @file   MeshManager.h
//* @brief  
//* @note   メッシュのリソースを管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"
#include "ManagerHeader.h"

namespace GAME_SYSTEMS
{
	class StaticMesh;
	class SkeletalMesh;

	class MeshManager
	{
		SINGLETON_CLASS(MeshManager);
		MANAGER_CLASS;

	public:
		SharedPtr<StaticMesh> GetStaticMesh(T_String fileName);
		SharedPtr<SkeletalMesh> GetSkeletalMesh(T_String fileName);

		void Releace();

	private:
		void SetUp();
		void ShutDown();

	private:
		T_String GetFilePath(T_String fileName);

	private:
		Unordered_Map <T_String, T_String> m_filePathList;
		Unordered_Map <T_String, SharedPtr<StaticMesh>> m_staticMeshList;
		Unordered_Map <T_String, SharedPtr<SkeletalMesh>> m_skeletalMeshList;

	};
}
