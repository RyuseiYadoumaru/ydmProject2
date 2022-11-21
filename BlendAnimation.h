//#pragma once
//#include "AnimationClip.h"
//
//
////class Animation;
//
//// ブレンドするアニメーション
//struct BlendSample
//{
//	AnimationClip* sample;      // モーション
//	float blendParameter;// ブレンド用
//};
//
//// ブレンド用の情報
//struct AnimationBlendInterpolationInfo
//{
//	AnimationClip* sample1;
//	AnimationClip* sample2;
//	float interpolationRate;
//};
//
//// ブレンドアニメーション
//class BlendAnimation : public gameSystems::Motion
//{
//public:
//	void AddBlendSample(AnimationClip* sample, float blendParameter = 0.0f);
//
//public:
//	Float32 virtual GetDuration(Animation* animation) override;
//
//	// アニメーションの姿勢を求める
//	virtual void CalcAnimationTransforms(
//		Vector<BoneTransform>& output,
//		Animation* animationo,
//		Float32 rate = 1.0f) override;
//
//public:
//	// ブレンド情報を計算する
//	void CalcBlendInterpolationInfo(
//		AnimationBlendInterpolationInfo& output,
//		float m_blendWeightParam);
//
//private:
//	std::vector<BlendSample> m_blendSamles;
//};

