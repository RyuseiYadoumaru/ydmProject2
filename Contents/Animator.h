//*****************************************************************************
//* @file   Animator.h
//* @brief  �A�j���[�^�[�N���X
//* @note   �A�j���[�V�����N���b�v�̊Ǘ��ƍĐ�
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once

#include "Miscellaneous.h"
#include "macro.h"
#include "std.h"

namespace GAME_SYSTEMS
{
	class SkinnedMeshRenderer;
	class Motion;
	class AnimationClip;
	class BlendAnimationClip;

	class Animator : public Miscellaneous
	{
	public:
		void AddAnimation(T_String aninName,SharedPtr<Motion> anim);
		void Play(T_String animationName);
		void Play(T_String blendName, Float32 blendParam);

		// �Đ�����
		Float32 GetPlayTimer() const noexcept { return m_playTimer; }

		// �Đ����x
		Float32 GetPlaySpeed() const noexcept { return m_playSpeed; }
		void SetPlaySpeed(Float32 speed) noexcept { m_playSpeed = speed;}

		// �u�����h
		SharedPtr<BlendAnimationClip> CreateBlendAnimation(T_String name);
		void SetBlendParam(Float32 blendParam) noexcept { m_blendParam = blendParam; }
	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	private:
		// �X�P���g���R���|�[�l���g
		SharedPtr<SkinnedMeshRenderer> m_skinnedRenderer;

		// ���[�V����
		Unordered_Map<T_String, SharedPtr<Motion>> m_motionList;
		SharedPtr<Motion> m_currentMotion = nullptr;
		T_String m_currentMotionName;

		// �Đ�����
		Float32 m_playSpeed = 1.0f;
		Float32 m_playTimer = 0.0f;

		// �u�����h
		Float32 m_blendParam = 1.0f;
	public:
		Animator() : Miscellaneous("Animator", Type::Animator) {}
		~Animator() = default;
	};
}
