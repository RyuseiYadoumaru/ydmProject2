//*****************************************************************************
//* @file   BlendAnimationClip.h
//* @brief  
//* @note   ブレンドアニメーション
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "Motion.h"
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class AnimationClip;

	// ブレンドサンプル
	struct  BlendSample
	{
		SharedPtr<AnimationClip> sample = nullptr;
		Float32 blendParam = 1.0f;
	};

	// ブレンド用の情報
	struct AnimationBlendInterpolationInfo
	{
		SharedPtr<AnimationClip> sample1 = nullptr;
		SharedPtr<AnimationClip> sample2 = nullptr;
		Float32 interpolationRate = 0.0f;
	};


	class BlendAnimationClip : public Motion
	{
	public:
		void AddBlendAnimation(SharedPtr<AnimationClip> blendAnim, Float32 blendParam);
		void SetBlendParam(Float32 param) noexcept { m_blendParam = param; }

	public:
		virtual Float32 GetDuration() override;

	private:
		// アニメーションの姿勢を求める
		virtual void CreateAnimationTransform(Float32 time, Float32 rate = 1.0f) override;
		void CalcBlendInterpolationInfo(AnimationBlendInterpolationInfo* blendInfo, Float32 blendParam);

	private:
		Vector<BlendSample> m_blendSampleList;
		Float32 m_blendParam = 1.0f;

	};
}
