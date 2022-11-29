//*****************************************************************************
//* @file   AnimationClip.h
//* @brief  アニメーションクリップ
//* @note   アニメーションのデータを管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "Motion.h"

//　アニメーションクリップ
namespace GAME_SYSTEMS
{
	class BlendAnimationClip;
	class Skeleton;
	class AnimationClip : public Motion
	{
	public:
		virtual Float32 GetDuration() override;

	private:
		// アニメーションのトランスフォームを生成する
		virtual void CreateAnimationTransform(Float32 time, Float32 rate = 1.0f) override;
		// アニメーションの補間用の情報取得
		void CalcAnimationInterpolationInfo(AnimationInterpolationInfo& output, Float32 currentTime);
		friend GAME_SYSTEMS::BlendAnimationClip;
	};
}