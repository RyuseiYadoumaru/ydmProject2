//*****************************************************************************
//* @file   Animator.cpp
//* @brief  アニメータークラス
//* @note   アニメーションクリップの管理と再生
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
		MessageWindow::Error("スケルトンレンダーがコンポーネントされていません!");
	}
}

void GAME_SYSTEMS::Animator::Update()
{
	if (m_motionList.empty() == true || m_currentMotion == nullptr)
	{
		return;
	}

	m_playTimer += Timer::DeltaTime() * m_playSpeed;

	// 再生終了したとき
	if (m_playTimer > m_currentMotion->GetDuration(m_blendParam))
	{
		// ループ再生
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

	// アニメーション行列計算
	Vector<MY_MATH::Matrix4x4> animMtx;
	auto skeleton = m_skinnedRenderer->GetSkeleton();
	uInt32 boneNum = skeleton->GetBoneNum();
	m_currentMotion->CalcAnimationMatrix(animMtx, boneNum, m_playTimer);

	// ボーン行列更新
	skeleton->CreateAnimationMatrix(animMtx);
}

void GAME_SYSTEMS::Animator::End()
{
	m_skinnedRenderer = nullptr;
	m_motionList.clear();
	m_currentMotion = nullptr;
}
