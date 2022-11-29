//*****************************************************************************
//* @file   Animator.cpp
//* @brief  �A�j���[�^�[�N���X
//* @note   �A�j���[�V�����N���b�v�̊Ǘ��ƍĐ�
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Animator.h"
#include "Motion.h"
#include "BlendAnimationClip.h"
#include "AnimationClip.h"
#include "Skeleton.h"

#include "SkinnedMeshRenderer.h"
#include "GameObject.h"

#include "Timer.h"
#include "Debug.h"

#include "../System/MessageWindow.h"


USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS


void GAME_SYSTEMS::Animator::AddAnimation(T_String animName, SharedPtr<Motion> anim)
{
	m_motionList[animName] = anim;
}

void GAME_SYSTEMS::Animator::Play(T_String animationName)
{
	if (m_motionList.contains(animationName) == true &&
		m_currentMotionName != animationName)
	{
		m_currentMotion = m_motionList[animationName];
		m_currentMotionName = animationName;
		m_playTimer = 0.0f;
	}
}

void GAME_SYSTEMS::Animator::Play(T_String blendName, Float32 blendParam)
{
	if (m_motionList.contains(blendName) == true)
	{
		// �u�����h�A�j���[�V�����擾
		auto blendAnim = std::dynamic_pointer_cast<BlendAnimationClip>(m_motionList[blendName]);
		if (blendAnim != nullptr)
		{
			// �u�����h�p�����[�^�Z�b�g
			blendAnim->SetBlendParam(blendParam);
			if (m_currentMotionName != blendName)
			{
				// �O��Ɩ��O���Ⴄ�Ƃ��ɃA�j���[�V�����؂�ւ�
				m_currentMotion = blendAnim;
				m_currentMotionName = blendName;
				m_playTimer = 0.0f;
			}
		}
	}
}

SharedPtr<BlendAnimationClip> GAME_SYSTEMS::Animator::CreateBlendAnimation(T_String name)
{
	auto blendAnim = std::make_shared<BlendAnimationClip>();
	m_motionList[name] = blendAnim;
	return blendAnim;
}

void GAME_SYSTEMS::Animator::Start()
{
	//m_skinnedRenderer = GetOwner()->GetComponent<SkinnedMeshRenderer>();
	if (m_skinnedRenderer == nullptr)
	{
		Debug::LogError("AnimatorError : ", GetOwner()->ToString());
		MessageWindow::Error("�X�P���g�������_�[���R���|�[�l���g����Ă��܂���!");
	}
}

void GAME_SYSTEMS::Animator::Update()
{
	if (m_motionList.empty() == true || m_currentMotion == nullptr)
	{
		return;
	}

	m_playTimer += Timer::DeltaTime() * m_playSpeed;

	// �Đ��I�������Ƃ�
	if (m_playTimer > m_currentMotion->GetDuration())
	{
		// ���[�v�Đ�
		if (m_currentMotion->GetIsLoop() == true)
		{
			m_playTimer = 0.0f;
		}
	}
	else if (m_playTimer < 0.0f)
	{
		if (m_currentMotion->GetIsLoop() == true)
		{
			m_playTimer = m_currentMotion->GetDuration();
		}
	}

	// �A�j���[�V�����s��v�Z
	Vector<MY_MATH::Matrix4x4> animMtx;
	//auto skeleton = m_skinnedRenderer->GetSkeleton();
	//uInt32 boneNum = skeleton->GetBoneNum();
	//m_currentMotion->CalcAnimationMatrix(animMtx, boneNum, m_playTimer);

	// �{�[���s��X�V
	//skeleton->CreateAnimationMatrix(animMtx);
}

void GAME_SYSTEMS::Animator::End()
{
	m_skinnedRenderer = nullptr;
	m_motionList.clear();
	m_currentMotion = nullptr;
}
