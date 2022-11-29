//*****************************************************************************
//* @file   AnimationClip.h
//* @brief  �A�j���[�V�����N���b�v
//* @note   �A�j���[�V�����̃f�[�^���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "Motion.h"

//�@�A�j���[�V�����N���b�v
namespace GAME_SYSTEMS
{
	class BlendAnimationClip;
	class Skeleton;
	class AnimationClip : public Motion
	{
	public:
		virtual Float32 GetDuration() override;

	private:
		// �A�j���[�V�����̃g�����X�t�H�[���𐶐�����
		virtual void CreateAnimationTransform(Float32 time, Float32 rate = 1.0f) override;
		// �A�j���[�V�����̕�ԗp�̏��擾
		void CalcAnimationInterpolationInfo(AnimationInterpolationInfo& output, Float32 currentTime);
		friend GAME_SYSTEMS::BlendAnimationClip;
	};
}