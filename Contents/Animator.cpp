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
		// ブレンドアニメーション取得
		auto blendAnim = std::dynamic_pointer_cast<BlendAnimationClip>(m_motionList[blendName]);
		if (blendAnim != nullptr)
		{
			// ブレンドパラメータセット
			blendAnim->SetBlendParam(blendParam);
			if (m_currentMotionName != blendName)
			{
				// 前回と名前が違うときにアニメーション切り替え
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
	if (m_playTimer > m_currentMotion->GetDuration())
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
			m_playTimer = m_currentMotion->GetDuration();
		}
	}

	// アニメーション行列計算
	Vector<MY_MATH::Matrix4x4> animMtx;
	//auto skeleton = m_skinnedRenderer->GetSkeleton();
	//uInt32 boneNum = skeleton->GetBoneNum();
	//m_currentMotion->CalcAnimationMatrix(animMtx, boneNum, m_playTimer);

	// ボーン行列更新
	//skeleton->CreateAnimationMatrix(animMtx);
}

void GAME_SYSTEMS::Animator::End()
{
	m_skinnedRenderer = nullptr;
	m_motionList.clear();
	m_currentMotion = nullptr;
}
