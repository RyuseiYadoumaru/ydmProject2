//*****************************************************************************
//* @file   Mouse.h
//* @brief  �}�E�X
//* @note   �}�E�X�̓��͂��Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************
#pragma once
#include "Vector2.h"
#include "macro.h"
#include "std.h"
namespace GAME_SYSTEMS
{
	enum class MouseCode
	{
		Left = 0,	// ���N���b�N
		Right,		// �E�N���b�N
		Center		// �Z���^�[�z�C�[��
	};

	class Mouse
	{
	public:
		/**
		 * �}�E�X�N���b�N.
		 */
		static bool Click(MouseCode mouseCode);

		/**
		 * �}�E�X�N���b�N�����[�X.
		 */
		static bool Up(MouseCode mouseCode);

		/**
		 * �J�[�\�����W�擾.
		 */
		static myMath::Vector2 CursorPosition();


		/**
		 * �J�[�\���ړ��ʎ擾.
		 */
		static myMath::Vector2 CursorVelocity();

	};
}
