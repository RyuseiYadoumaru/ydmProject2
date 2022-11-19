//*****************************************************************************
//* @file   TextureManager.h
//* @brief  
//* @note   ���[�h���ꂽ�e�N�X�`�����Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "ManagerHeader.h"

namespace GAME_SYSTEMS
{
	class Texture;
	class TextureManager
	{
		SINGLETON_CLASS(TextureManager);
		MANAGER_CLASS;

	public:
		SharedPtr<Texture> GetTexture(T_String name);
		void Releace();

	private:
		void SetUp();
		void ShutDown();

	private:
		T_String GetFilePath(T_String fileName);

	private:
		Unordered_Map <T_String, T_String> m_filePathList;
		Unordered_Map <T_String, SharedPtr<Texture>> m_textureList;

	};
}
