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
	if (m_motionList.contains(animationName) == true)
	{
		m_currentMotion = m_motionList[animationName];
	}
}

void GAME_SYSTEMS::Animator::Start()
{
	m_skinnedRenderer = GetOwner()->GetComponent<SkinnedMeshRenderer>();
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
	if (m_playTimer > m_currentMotion->GetDuration(m_blendParam))
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
			m_playTimer = m_currentMotion->GetDuration(m_blendParam);
		}
	}

	// �A�j���[�V�����s��v�Z
	Vector<MY_MATH::Matrix4x4> animMtx;
	auto skeleton = m_skinnedRenderer->GetSkeleton();
	uInt32 boneNum = skeleton->GetBoneNum();
	m_currentMotion->CalcAnimationMatrix(animMtx, boneNum, m_playTimer);

	// �{�[���s��X�V
	skeleton->CreateAnimationMatrix(animMtx);
}

void GAME_SYSTEMS::Animator::End()
{
	m_skinnedRenderer = nullptr;
	m_motionList.clear();
	m_currentMotion = nullptr;
}
