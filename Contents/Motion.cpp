//*****************************************************************************
//* @file   Motion.cpp
//* @brief  
//* @note   モーションデータの基底クラス
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

	// アニメーション情報取得
	auto animation = assimpScene->GetScene()->mAnimations[animationIndex];

	SetName(animation->mName.C_Str());
	this->m_TicksPerSecond = animation->mTicksPerSecond;
	this->m_keyFrameDuration = animation->mDuration;

	// キーフレーム用配列初期化
	const int boneNum = assimpScene->GetBoneNum();
	ResizeKeyFrames(boneNum);

	// ボーン用のキーフレーム取得
	const int channelNum = animation->mNumChannels;
	for (int i = 0; i < channelNum; i++)
	{
		auto nodeAnim = animation->mChannels[i];
		int boneIndex = assimpScene->GetBoneIndexByName(nodeAnim->mNodeName.C_Str());

		// ポジションのキーフレーム情報取得
		InitPositionKeyFrame(nodeAnim, boneIndex);

		// 回転のキーフレーム情報取得
		InitRotationKeyFrame(nodeAnim, boneIndex);
	}

	m_isLoad = true;
	return true;

}

void GAME_SYSTEMS::Motion::CalcAnimationMatrix(
	Animation* animation,
	Vector<myMath::Matrix4x4>* outputMatrix)
{
	// アニメーション行列用配列初期化
	const Int32 boneNum = animation->GetSkeleton()->GetBoneNum();
	outputMatrix->clear();
	outputMatrix->resize(boneNum);

	std::vector<BoneTransform> outputTransforms;
	CalcAnimationTransforms(outputTransforms, animation);

	// 各ボーンごとにアニメーション行列を求める
	for (Int32 boneIndex = 0; boneIndex < boneNum; boneIndex++)
	{
		outputMatrix[boneIndex].push_back(outputTransforms[boneIndex].GetMatrix());
	}
}