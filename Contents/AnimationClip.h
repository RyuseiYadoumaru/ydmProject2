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
	class AnimationClip : public Motion
	{
	public:
		virtual Float32 GetDuration(Animation* animation) override;

		// �A�j���[�V�����̎p�������߂�
		virtual void CalcAnimationTransforms(
			Vector<BoneTransform>& output,
			const uInt32 boneNum,
			Float32 time,
			Float32 rate) override;

		// �A�j���[�V�����̕�ԗp�̏��擾
		void CalcAnimationInterpolationInfo(
			AnimationInterpolationInfo& output,
			Float32 currentTime);
	};
}