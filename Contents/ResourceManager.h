//*****************************************************************************
//* @file   ResourceManager.h
//* @brief  
//* @note   ���b�V���̃��\�[�X���Ǘ�����
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
	class ModelData;
	class Model;
	class Texture;
	class AnimationClip;

	class ResourceManager
	{
		SINGLETON_CLASS(ResourceManager);
		MANAGER_CLASS;

		enum class FileData
		{
			Animation,
			Audio,
			Model,
			Sprite
		};
	public:
		enum class GeometryType
		{
			Terrain
		};

	public:
		// �t�@�C��
		T_String GetFilePath(T_String fileName);
		
		// �A�j���[�V����
		SharedPtr<AnimationClip> GetAnimationClip(T_String fileName);
		
		// ���f��
		SharedPtr<ModelData> GetModelData(T_String fileName);
		SharedPtr<Model> GetGeometry(GeometryType type) noexcept { return m_geometryList[type]; }
		
		// �e�N�X�`��
		SharedPtr<Texture> GetTexture(T_String fileName);


		void Releace();

	private:
		void SetUp();
		void ShutDown();

	private:
		bool CheckExt(T_String ext, FileData data);

	private:
		// �t�@�C��
		Unordered_Map <T_String, T_String> m_filePathList;
		Unordered_Map<FileData, Vector<T_String>> m_fileDataExtList;
		
		// �A�j���[�V����
		Unordered_Map<T_String, SharedPtr<AnimationClip>> m_animationList;

		// ���f��
		Unordered_Map <GeometryType, SharedPtr<Model>> m_geometryList;
		Unordered_Map <T_String, SharedPtr<ModelData>> m_modelDataList;

		// �X�v���C�g�e�N�X�`��
		Unordered_Map <T_String, SharedPtr<Texture>> m_textureList;
	};
}
