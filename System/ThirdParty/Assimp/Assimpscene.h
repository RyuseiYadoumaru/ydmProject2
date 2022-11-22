#pragma once
#include "std.h"

struct aiScene;
struct aiNode;

class AssimpScene
{
public:
	// ��������
	bool Init(T_String filename);
	// �I������
	void Exit();

	// �V�[���擾
	const aiScene* GetScene() const;

	// �A�j���[�V�����������Ă��邩
	bool HasAnimation();

	// �A�j���[�V�����̐�
	unsigned int GetAnimationsNum() const;

	// ���O����{�[���̃C���f�b�N�X���擾����
	int GetBoneIndexByName(std::string name) const;

	// �{�[���̐����擾
	uInt32 GetBoneNum() const;

private:
	// �{�[���̖��O�ƃC���f�b�N�X���֘A�t����}�b�v�쐬
	void CreateBoneIndexMap(aiNode* node);

private:
	const aiScene* m_Scene = nullptr;	// assimp scene

	// �{�[���̖��O�ƃC���f�b�N�X���֘A�t����
	Unordered_Map<T_String, int> m_boneIndexMap;
};