//*****************************************************************************
//* @file   Motion.cpp
//* @brief  
//* @note   ���[�V�����f�[�^�̊��N���X
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Motion.h"
#include "Skeleton.h"
#include "../System/ThirdParty/Assimp/Assimpscene.h"
#include "../Animation.h"

USING_GAME_SYSTEMS;

bool GAME_SYSTEMS::Motion::Load(AssimpScene* assimpScene, uInt32 animationIndex)
{
	if (assimpScene == nullptr ||
		animationIndex > assimpScene->GetAnimationsNum())
	{
		m_isLoad = false;
		return false;
	}

	// �A�j���[�V�������擾
	auto animation = assimpScene->GetScene()->mAnimations[animationIndex];

	SetName(animation->mName.C_Str());
	this->m_TicksPerSecond = animation->mTicksPerSecond;
	this->m_keyFrameDuration = animation->mDuration;

	// �L�[�t���[���p�z�񏉊���
	const int boneNum = assimpScene->GetBoneNum();
	ResizeKeyFrames(boneNum);

	// �{�[���p�̃L�[�t���[���擾
	const int channelNum = animation->mNumChannels;
	for (int i = 0; i < channelNum; i++)
	{
		auto nodeAnim = animation->mChannels[i];
		int boneIndex = assimpScene->GetBoneIndexByName(nodeAnim->mNodeName.C_Str());

		// �|�W�V�����̃L�[�t���[�����擾
		InitPositionKeyFrame(nodeAnim, boneIndex);

		// ��]�̃L�[�t���[�����擾
		InitRotationKeyFrame(nodeAnim, boneIndex);
	}

	m_isLoad = true;
	return true;

}

void GAME_SYSTEMS::Motion::CalcAnimationMatrix(
	Animation* animation,
	Vector<myMath::Matrix4x4>* outputMatrix)
{
	// �A�j���[�V�����s��p�z�񏉊���
	const Int32 boneNum = animation->GetSkeleton()->GetBoneNum();
	outputMatrix->clear();
	outputMatrix->resize(boneNum);

	std::vector<BoneTransform> outputTransforms;
	CalcAnimationTransforms(outputTransforms, animation);

	// �e�{�[�����ƂɃA�j���[�V�����s������߂�
	for (Int32 boneIndex = 0; boneIndex < boneNum; boneIndex++)
	{
		outputMatrix[boneIndex].push_back(outputTransforms[boneIndex].GetMatrix());
	}
}