//*****************************************************************************
//* @file   BlendAnimationClip.h
//* @brief  
//* @note   ブレンドアニメーション
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "BlendAnimationClip.h"
#include "AnimationClip.h"

void GAME_SYSTEMS::BlendAnimationClip::AddBlendAnimation(SharedPtr<AnimationClip> blendAnim, Float32 blendParam)
{
    BlendSample blend;
    blend.sample = std::make_shared<AnimationClip>();
    blend.sample = blendAnim;
    blend.blendParam = blendParam;
    m_blendSampleList.emplace_back(blend);
}

Float32 GAME_SYSTEMS::BlendAnimationClip::GetDuration()
{
	AnimationBlendInterpolationInfo info;
	CalcBlendInterpolationInfo(&info, m_blendParam);

	Float32 result;

	const Float32 d1 = info.sample1->GetDuration();
	const Float32 d2 = info.sample2->GetDuration();
	const Float32 rate = info.interpolationRate;

	result = d1 * (1.0f - rate) + rate * d2;

	return result;
}

void GAME_SYSTEMS::BlendAnimationClip::CalcAnimationTransforms(
	Vector<BoneTransform>& output,
	const uInt32 boneNum,
	Float32 time,
	Float32 rate)
{
	// アニメーション行列用配列初期化
	output.clear();
	output.resize(boneNum);

	// 補間すべきアニメーションを計算して求める
	AnimationBlendInterpolationInfo info;
	CalcBlendInterpolationInfo(&info, m_blendParam);

	Vector<BoneTransform> boneTransforms1, boneTransforms2;

	Float32 duration = GetDuration();

	Float32 rate1 = info.sample1->GetDuration() / duration;
	Float32 rate2 = info.sample2->GetDuration() / duration;


	// 補間する二つのアニメーションの姿勢を求める
	info.sample1->CalcAnimationTransforms(boneTransforms1, boneNum, time, rate1);
	info.sample2->CalcAnimationTransforms(boneTransforms2, boneNum, time, rate2);

	// ブレンドする
	for (Int32 i = 0; i < boneNum; i++)
	{
		output[i] = BoneTransform::Lerp(
			boneTransforms1[i],
			boneTransforms2[i],
			info.interpolationRate);
	}

}

void GAME_SYSTEMS::BlendAnimationClip::CalcBlendInterpolationInfo(
	AnimationBlendInterpolationInfo* blendInfo,
	Float32 blendParam)
{
	if (m_blendSampleList.empty() == true)
	{
		blendInfo->sample1 = nullptr;
		blendInfo->sample2 = nullptr;
		blendInfo->interpolationRate = 0.0f;
		return;
	}

	Float32 low = -100000.0f;
	Float32 high = 100000.0f;
	for (auto& blendSamle : m_blendSampleList)
	{
		Float32 diff = blendSamle.blendParam - blendParam;

		if (diff <= 0.0f && diff > low)
		{
			blendInfo->sample1 = blendSamle.sample;
			low = diff;
		}

		if (diff >= 0.0f && diff < high)
		{
			blendInfo->sample2 = blendSamle.sample;
			high = diff;
		}
	}

	if (abs(high - low) > FLT_EPSILON)
	{
		blendInfo->interpolationRate = -low / (high - low);
	}
	else
	{
		blendInfo->interpolationRate = 0.0f;
	}
}
