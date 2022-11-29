//*****************************************************************************
//* @file   Motion.cpp
//* @brief  
//* @note   モーションデータの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "../System/ThirdParty/Assimp/AssimpHeader.h"
#include "Motion.h"
#include "Skeleton.h"
#include "Debug.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;

bool GAME_SYSTEMS::Motion::Load(const aiAnimation* assimpAnimation)
{
	// アニメーション情報取得
	auto animation = assimpAnimation;
	m_name = animation->mName.C_Str();
	m_ticksPerSecond	= static_cast<Float32>(animation->mTicksPerSecond);
	m_keyFrameDuration	= static_cast<Float32>(animation->mDuration);
	m_keyFrameNum = static_cast<uInt32>(m_keyFrameDuration) + 1;
	// キーアニメーション初期化
	const uInt32 channelNum = animation->mNumChannels;
	for (uInt32 i = 0; i < channelNum; i++)
	{
		// アニメーションノード取得
		auto nodeAnim = animation->mChannels[i];
		auto boneName = nodeAnim->mNodeName.C_Str();
		m_keyNameList.emplace_back(boneName);
		
		// キーアニメーション作成
		m_boneKeyFrameList[boneName].resize(m_keyFrameNum);	
		for (auto& key : m_boneKeyFrameList[boneName])
		{
			key.position = MY_MATH::Vector3(0.0f, 0.0f, 0.0f);
			key.rotation = MY_MATH::Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
			key.shouldLerpPosition = true;
			key.shouldSlerpRotation = true;
		}

		// ポジションのキーフレーム情報取得
		InitPositionKeyFrame(nodeAnim, boneName);
		// 回転のキーフレーム情報取得
		InitRotationKeyFrame(nodeAnim, boneName);
	}
	return true;
}

bool GAME_SYSTEMS::Motion::Load(T_String filePath)
{
	// 初期化
	m_animationLoader.Init(filePath);

	if (m_animationLoader.GetScene()->HasAnimations() == false)
	{
		m_animationLoader.Exit();
		TOOLS::Debug::Assert(true, "アニメーションデータがありません : " + filePath);
		return false;
	}

	// アニメーション情報取得
	auto animation = m_animationLoader.GetScene()->mAnimations[0];
	m_name = animation->mName.C_Str();
	m_ticksPerSecond = static_cast<Float32>(animation->mTicksPerSecond);
	m_keyFrameDuration = static_cast<Float32>(animation->mDuration);
	m_keyFrameNum = static_cast<uInt32>(m_keyFrameDuration) + 1;
	// キーアニメーション初期化
	const uInt32 channelNum = animation->mNumChannels;
	for (uInt32 i = 0; i < channelNum; i++)
	{
		// アニメーションノード取得
		auto nodeAnim = animation->mChannels[i];
		auto boneName = nodeAnim->mNodeName.C_Str();
		m_keyNameList.emplace_back(boneName);

		// キーアニメーション作成
		m_boneKeyFrameList[boneName].resize(m_keyFrameNum);
		for (auto& key : m_boneKeyFrameList[boneName])
		{
			key.position = MY_MATH::Vector3(0.0f, 0.0f, 0.0f);
			key.rotation = MY_MATH::Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
			key.shouldLerpPosition = true;
			key.shouldSlerpRotation = true;
		}

		// ポジションのキーフレーム情報取得
		InitPositionKeyFrame(nodeAnim, boneName);
		// 回転のキーフレーム情報取得
		InitRotationKeyFrame(nodeAnim, boneName);
	}
	m_animationLoader.Exit();
	return true;
}

void GAME_SYSTEMS::Motion::Releace()
{
	m_boneKeyFrameList.clear();
	m_boneTransformList.clear();
	m_keyNameList.clear();
}

void GAME_SYSTEMS::Motion::CalcAnimationTransform(Skeleton* skeleton, Float32 time, Float32 rate)
{
	if (skeleton == nullptr)
	{
		return;
	}
	// アニメーショントランスフォーム生成
	CreateAnimationTransform(time, rate);

	// アニメーショントランスフォームセット
	for (auto& boneTransform : m_boneTransformList)
	{
		Int32 boneIndex = skeleton->GetBoneIndexByName(boneTransform.first);
		if (boneIndex >= 0)
		{
			auto bone = skeleton->GetBoneByIndex(boneIndex);
			bone->SetBoneTransform(boneTransform.second);
		}
	}
	// スケルトン行列を更新する
	skeleton->UpdateBoneMatrix();
}

void GAME_SYSTEMS::Motion::InitPositionKeyFrame(aiNodeAnim* nodeAnim, T_String boneName)
{
	const Int32 posKeyNum = nodeAnim->mNumPositionKeys;
	for (Int32 keyIndex = 0; keyIndex < posKeyNum; keyIndex++)
	{
		// 各キーの情報取得
		Int32 frameTime = static_cast<Int32>(nodeAnim->mPositionKeys[keyIndex].mTime);
		aiVector3D pos = nodeAnim->mPositionKeys[keyIndex].mValue;

		// フレームごとの情報を取得する
		 m_boneKeyFrameList[boneName][frameTime].position = myMath::Vector3(pos.x, pos.y, pos.z);
		 m_boneKeyFrameList[boneName][frameTime].shouldLerpPosition = false;
	}
	// キーフレームをLerp補完する
	InitLerpPositionKeyFrame(boneName);
}

void GAME_SYSTEMS::Motion::InitRotationKeyFrame(aiNodeAnim* nodeAnim, T_String boneName)
{
	const Int32 rotKeyNum = nodeAnim->mNumRotationKeys;
	for (Int32 keyIndex = 0; keyIndex < rotKeyNum; keyIndex++)
	{
		// 各キーの情報取得
		Int32 frameTime = static_cast<Int32>(nodeAnim->mRotationKeys[keyIndex].mTime);
		aiQuaternion rot = nodeAnim->mRotationKeys[keyIndex].mValue;

		// ふれーむごとの情報を取得する
		 m_boneKeyFrameList[boneName][frameTime].rotation = MY_MATH::Quaternion(rot.x, rot.y, rot.z, rot.w);
		 m_boneKeyFrameList[boneName][frameTime].shouldSlerpRotation = false;
	}
	// キーフレームをSlerp補間する
	InitSlerpRotationKeyFrame(boneName);
}

void GAME_SYSTEMS::Motion::InitLerpPositionKeyFrame(T_String boneName)
{
	const Int32 keyNum = static_cast<Int32>(m_boneKeyFrameList[boneName].size());
	for (Int32 i = 0; i < keyNum; i++)
	{
		auto& key = m_boneKeyFrameList[boneName][i];
		if (key.shouldLerpPosition)
		{
			Int32 keyIndex1 = -1;
			Int32 keyIndex2 = -1;

			for (Int32 index = i - 1; index >= 0; index--)
			{
				if (m_boneKeyFrameList[boneName][index].shouldLerpPosition == false)
				{
					keyIndex1 = index;
					break;
				}
			}

			for (Int32 index = i + 1; index < keyNum; index++)
			{
				if (m_boneKeyFrameList[boneName][index].shouldLerpPosition == false)
				{
					keyIndex2 = index;
					break;
				}
			}

			// 補間がない場合
			if (keyIndex2 < 0 && keyIndex1 >= 0)
			{
				key.position = m_boneKeyFrameList[boneName][keyIndex1].position;
			}

			else if (keyIndex1 < 0 && keyIndex2 >= 0)
			{
				key.position = m_boneKeyFrameList[boneName][keyIndex2].position;
			}

			else if (keyIndex1 >= 0 && keyIndex2 >= 0)
			{
				Float32 rate = static_cast<Float32>(i - keyIndex1) / static_cast<Float32>(keyIndex2 - keyIndex1);
				KeyFrame& key1 = m_boneKeyFrameList[boneName][keyIndex1];
				KeyFrame& key2 = m_boneKeyFrameList[boneName][keyIndex2];
				MY_MATH::Vector3 pos = MY_MATH::Vector3::Larp(key1.position, key2.position, rate);
				key.position = pos;
			}
		}
	}

}

void GAME_SYSTEMS::Motion::InitSlerpRotationKeyFrame(T_String boneName)
{
	const Int32 keyNum = static_cast<Int32>(m_boneKeyFrameList[boneName].size());
	for (Int32 i = 0; i < keyNum; i++)
	{
		auto& key = m_boneKeyFrameList[boneName][i];
		if (key.shouldSlerpRotation)
		{
			int keyIndex1 = -1;
			int keyIndex2 = -1;

			for (int index = i - 1; index >= 0; index--)
			{
				if (m_boneKeyFrameList[boneName][index].shouldSlerpRotation == false)
				{
					keyIndex1 = index;
					break;
				}
			}

			for (Int32 index = i + 1; index < keyNum; index++)
			{
				if (m_boneKeyFrameList[boneName][index].shouldSlerpRotation == false)
				{
					keyIndex2 = index;
					break;
				}
			}

			// 補間がない場合
			if (keyIndex2 < 0 && keyIndex1 >= 0)
			{
				key.rotation = m_boneKeyFrameList[boneName][keyIndex1].rotation;
			}

			else if (keyIndex1 < 0 && keyIndex2 >= 0)
			{
				key.rotation = m_boneKeyFrameList[boneName][keyIndex2].rotation;
			}

			else if (keyIndex1 >= 0 && keyIndex2 >= 0)
			{
				Float32 rate = static_cast<Float32>(i - keyIndex1) / static_cast<Float32>(keyIndex2 - keyIndex1);
				KeyFrame& key1 = m_boneKeyFrameList[boneName][keyIndex1];
				KeyFrame& key2 = m_boneKeyFrameList[boneName][keyIndex2];
				MY_MATH::Quaternion rot = MY_MATH::Quaternion::Slerp(key1.rotation, key2.rotation, rate);
				key1.rotation = rot;
			}
		}
	}
}
