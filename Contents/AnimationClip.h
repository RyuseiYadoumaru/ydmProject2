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
	class AnimationClip : public Motion
	{
	public:
		virtual Float32 GetDuration(Animation* animation) override;

		// アニメーションの姿勢を求める
		virtual void CalcAnimationTransforms(
			Vector<BoneTransform>& output,
			const uInt32 boneNum,
			Float32 time,
			Float32 rate) override;

		// アニメーションの補間用の情報取得
		void CalcAnimationInterpolationInfo(
			AnimationInterpolationInfo& output,
			Float32 currentTime);
	};
}