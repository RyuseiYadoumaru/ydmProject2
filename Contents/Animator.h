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
	class Motion;

	class Animator : public Miscellaneous
	{
	public:
		void AddAnimation(T_String ,SharedPtr<Motion> anim);
		void Play(T_String animationName);


	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	private:
		Unordered_Map<T_String, SharedPtr<Motion>> m_motionList;


	public:
		Animator() : Miscellaneous("Animator", Type::Animator) {}
		~Animator() = default;
	};
}
