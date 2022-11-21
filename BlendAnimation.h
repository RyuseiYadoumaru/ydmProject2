//#pragma once
//#include "AnimationClip.h"
//
//
////class Animation;
//
//// �u�����h����A�j���[�V����
//struct BlendSample
//{
//	AnimationClip* sample;      // ���[�V����
//	float blendParameter;// �u�����h�p
//};
//
//// �u�����h�p�̏��
//struct AnimationBlendInterpolationInfo
//{
//	AnimationClip* sample1;
//	AnimationClip* sample2;
//	float interpolationRate;
//};
//
//// �u�����h�A�j���[�V����
//class BlendAnimation : public gameSystems::Motion
//{
//public:
//	void AddBlendSample(AnimationClip* sample, float blendParameter = 0.0f);
//
//public:
//	Float32 virtual GetDuration(Animation* animation) override;
//
//	// �A�j���[�V�����̎p�������߂�
//	virtual void CalcAnimationTransforms(
//		Vector<BoneTransform>& output,
//		Animation* animationo,
//		Float32 rate = 1.0f) override;
//
//public:
//	// �u�����h�����v�Z����
//	void CalcBlendInterpolationInfo(
//		AnimationBlendInterpolationInfo& output,
//		float m_blendWeightParam);
//
//private:
//	std::vector<BlendSample> m_blendSamles;
//};

