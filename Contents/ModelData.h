//*****************************************************************************
//* @file   ModelData.h
//* @brief  
//* @note   3D���f���̑S�Ẵf�[�^�ێ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "../System/ThirdParty/Assimp/AssimpScene.h"
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class Model;
	class Skeleton;
	class Material;

	class ModelData
	{
		using ModelContainer	= Vector<SharedPtr<Model>>;

	public:
		void Load(T_String filePath);
		void Releace();

	public:
		// ���f��
		SharedPtr<Model> GetModel(uInt32 index);

		// �X�P���g��
		SharedPtr<Skeleton> GetSkeleton() const noexcept { return m_skeleton; }
		bool HasBone() const noexcept { return m_hasBone; }

		// �A�j���[�V����
		bool HasAnimation() const noexcept { return m_hasAnimation; }

	public:
		ModelData() = default;
		~ModelData() = default;

	private:
		void ProcessNode(aiNode* node);

	private:
		// ���f���f�[�^�̃��[�_�[
		SYSTEMS::AssimpScene m_modelLoader;

		// ���f��
		ModelContainer m_modelList;
		Unordered_Map<T_String, uInt32> m_modelNameList;
		bool m_enableLoadLevelOfDetail = false;

		// �X�P���g��
		SharedPtr<Skeleton> m_skeleton = nullptr;
		bool m_hasBone = false;

		// �A�j���[�V����
		bool m_hasAnimation = false;

	};
}
