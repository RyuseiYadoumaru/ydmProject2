//*****************************************************************************
//* @file   AssimpScene.h
//* @brief  
//* @note   Assimp�Ń��[�h�����f�[�^���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiBone;
struct aiFace;


namespace SYSTEMS
{
	class AssimpScene
	{
	public:
		// ��������
		bool Init(T_String filename);
		// �I������
		void Exit();

		// �V�[���擾
		const aiScene* GetScene() const;

		// ���b�V��
		bool HasMesh() const noexcept;
		uInt32 GetMeshNum() const noexcept;

		// �A�j���[�V����
		bool HasAnimation();
		uInt32 GetAnimationsNum() const;

	private:
		const aiScene* m_Scene = nullptr;

		// �{�[���̖��O�ƃC���f�b�N�X���֘A�t����
		Unordered_Map<T_String, int> m_boneIndexList;
	};
}