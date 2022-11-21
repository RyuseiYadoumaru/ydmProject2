//*****************************************************************************
//* @file   Motion.cpp
//* @brief  
//* @note   モーションデータの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include <assimp\scene.h>
#include "../System/ThirdParty/Assimp/Assimpscene.h"
#include "Motion.h"
#include "Skeleton.h"
#include "../Animation.h"

USING_GAME_SYSTEMS;

bool GAME_SYSTEMS::Motion::Load(AssimpScene* assimpScene, uInt32 animationIndex)
{
	if (assimpScene == nullptr ||
		animationIndex > assimpScene->GetAnimationsNum() ||
		assimpScene->HasAnimation() == false)
	{
		m_isLoad = false;
		return false;
	}

	// アニメーション情報取得
	auto animation = assimpScene->GetScene()->mAnimations[animationIndex];

	m_name = animation->mName.C_Str();
	m_ticksPerSecond = animation->mTicksPerSecond;
	m_keyFrameDuration = animation->mDuration;

	// キーフレーム用配列初期化
	const Int32 boneNum = assimpScene->GetBoneNum();
	ResizeKeyFrameList(boneNum);

	// ボーン用のキーフレーム取得
	const Int32 channelNum = animation->mNumChannels;
	for (int i = 0; i < channelNum; i++)
	{
		auto nodeAnim = animation->mChannels[i];
		Int32 boneIndex = assimpScene->GetBoneIndexByName(nodeAnim->mNodeName.C_Str());
		// ポジションのキーフレーム情報取得
		InitPositionKeyFrame(nodeAnim, boneIndex);
		// 回転のキーフレーム情報取得
		InitRotationKeyFrame(nodeAnim, boneIndex);
	}
	m_isLoad = true;
	return true;
}

void GAME_SYSTEMS::Motion::CalcAnimationMatrix(Vector<MY_MATH::Matrix4x4>& outMtxList, const uInt32 boneNum, Float32 time)
{
	// アニメーション行列用配列初期化
	outMtxList.clear();
	outMtxList.resize(boneNum);

	// アニメーショントランスフォーム生成
	Vector<BoneTransform> outputTransforms;
	CalcAnimationTransforms(outputTransforms, boneNum, time);

	// 各ボーンごとにアニメーション行列を求める
	for (Int32 boneIndex = 0; boneIndex < boneNum; boneIndex++)
	{
		outMtxList[boneIndex].Set(outputTransforms[boneIndex].GetMatrix());
	}
}

void GAME_SYSTEMS::Motion::ResizeKeyFrameList(const Int32 boneNum)
{
	// キーフレーム用配列初期化
	m_boneKeyFrameList.clear();
	m_boneKeyFrameList.resize(boneNum);

	// フレーム数分容量を確保
	for (auto& boneKeyFrame : m_boneKeyFrameList)
	{
		boneKeyFrame.resize(m_keyFrameDuration + 1);

		for (auto& key : boneKeyFrame)
		{
			key.position = MY_MATH::Vector3(0.0f, 0.0f, 0.0f);
			key.rotation = MY_MATH::Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
			key.shouldLerpPosition = true;
			key.shouldSlerpRotation = true;
		}
	}
}

void GAME_SYSTEMS::Motion::InitPositionKeyFrame(aiNodeAnim* nodeAnim, const Int32 boneIndex)
{
	const Int32 posKeyNum = nodeAnim->mNumPositionKeys;
	for (Int32 keyIndex = 0; keyIndex < posKeyNum; keyIndex++)
	{
		// 各キーの情報取得
		Int32 frameTime = nodeAnim->mPositionKeys[keyIndex].mTime;
		aiVector3D pos = nodeAnim->mPositionKeys[keyIndex].mValue;

		auto& key = m_boneKeyFrameList[boneIndex][frameTime];
		key.position = myMath::Vector3(pos.x, pos.y, pos.z);
		key.shouldLerpPosition = false;
	}
	// キーフレームをLerp補完する
	InitLerpPositionKeyFrame(boneIndex);
}

void GAME_SYSTEMS::Motion::InitRotationKeyFrame(aiNodeAnim* nodeAnim, const Int32 boneIndex)
{
	const Int32 rotKeyNum = nodeAnim->mNumRotationKeys;
	for (Int32 keyIndex = 0; keyIndex < rotKeyNum; keyIndex++)
	{
		// 各キーの情報取得
		Int32 frameTime = nodeAnim->mRotationKeys[keyIndex].mTime;
		aiQuaternion rot = nodeAnim->mRotationKeys[keyIndex].mValue;

		auto& key = m_boneKeyFrameList[boneIndex][frameTime];
		key.rotation = MY_MATH::Quaternion(rot.x, rot.y, rot.z, rot.w);
		key.shouldSlerpRotation = false;
	}
	// キーフレームをSlerp補間する
	InitSlerpRotationKeyFrame(boneIndex);
}

void GAME_SYSTEMS::Motion::InitLerpPositionKeyFrame(Int32 boneIndex)
{
	const Int32 keyNum = m_boneKeyFrameList[boneIndex].size();
	for (Int32 i = 0; i < keyNum; i++)
	{
		auto& key = m_boneKeyFrameList[boneIndex][i];
		if (key.shouldLerpPosition)
		{
			Int32 keyIndex1 = -1;
			Int32 keyIndex2 = -1;

			for (Int32 index = i - 1; index >= 0; index--)
			{
				if (m_boneKeyFrameList[boneIndex][index].shouldLerpPosition == false)
				{
					keyIndex1 = index;
					break;
				}
			}

			for (Int32 index = i + 1; index < keyNum; index++)
			{
				if (m_boneKeyFrameList[boneIndex][index].shouldLerpPosition == false)
				{
					keyIndex2 = index;
					break;
				}
			}

			// 補間がない場合
			if (keyIndex2 < 0 && keyIndex1 >= 0)
			{
				key.position = m_boneKeyFrameList[boneIndex][keyIndex1].position;
			}

			else if (keyIndex1 < 0 && keyIndex2 >= 0)
			{
				key.position = m_boneKeyFrameList[boneIndex][keyIndex2].position;
			}

			else if (keyIndex1 >= 0 && keyIndex2 >= 0)
			{
				Float32 rate = static_cast<Float32>(i - keyIndex1) / static_cast<Float32>(keyIndex2 - keyIndex1);
				KeyFrame& key1 = m_boneKeyFrameList[boneIndex][keyIndex1];
				KeyFrame& key2 = m_boneKeyFrameList[boneIndex][keyIndex2];
				MY_MATH::Vector3 pos = MY_MATH::Vector3::Larp(key1.position, key2.position, rate);
				key.position = pos;
			}
		}
	}

}

void GAME_SYSTEMS::Motion::InitSlerpRotationKeyFrame(Int32 boneIndex)
{
	const Int32 keyNum = m_boneKeyFrameList[boneIndex].size();
	for (Int32 i = 0; i < keyNum; i++)
	{
		auto& key = m_boneKeyFrameList[boneIndex][i];
		if (key.shouldSlerpRotation)
		{
			int keyIndex1 = -1;
			int keyIndex2 = -1;

			for (int index = i - 1; index >= 0; index--)
			{
				if (m_boneKeyFrameList[boneIndex][index].shouldSlerpRotation == false)
				{
					keyIndex1 = index;
					break;
				}
			}

			for (Int32 index = i + 1; index < keyNum; index++)
			{
				if (m_boneKeyFrameList[boneIndex][index].shouldSlerpRotation == false)
				{
					keyIndex2 = index;
					break;
				}
			}

			// 補間がない場合
			if (keyIndex2 < 0 && keyIndex1 >= 0)
			{
				key.rotation = m_boneKeyFrameList[boneIndex][keyIndex1].rotation;
			}

			else if (keyIndex1 < 0 && keyIndex2 >= 0)
			{
				key.rotation = m_boneKeyFrameList[boneIndex][keyIndex2].rotation;
			}

			else if (keyIndex1 >= 0 && keyIndex2 >= 0)
			{
				Float32 rate = static_cast<Float32>(i - keyIndex1) / static_cast<Float32>(keyIndex2 - keyIndex1);
				KeyFrame& key1 = m_boneKeyFrameList[boneIndex][keyIndex1];
				KeyFrame& key2 = m_boneKeyFrameList[boneIndex][keyIndex2];
				MY_MATH::Quaternion rot = MY_MATH::Quaternion::Slerp(key1.rotation, key2.rotation, rate);
				key1.rotation = rot;
			}
		}
	}
}
