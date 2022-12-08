//*****************************************************************************
//* @file   Statemachine.h
//* @brief  �X�e�[�g�}�V�[���̊��N���X
//* @note   FSM (FiniteStateMachine) : �L����ԋ@�B
//* 
//* @author YadoumaruRyusei
//* @date   October 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"


namespace GAME_SYSTEMS
{
	class StateBase;
	class StateMachine
	{

		using StatePtr = SharedPtr<StateBase>;
		using StateType = T_String;
		using StateContainer = Unordered_Map<StateType, StatePtr>;

	public:
		void Update();
		void End();
	
	public:
		StateMachine() = default;
		~StateMachine() = default;

	public:
		/**
		 *  �X�e�[�g�o�^.
		 *
		 * !@param stateName : �X�e�[�g
		 * !@param state	 : �X�e�[�g�N���X
		 */
		void Register(StateType stateName, StatePtr state) noexcept
		{
			m_stateList.insert(std::make_pair(stateName, state));
		}

		/**
		 *  �X�e�[�g�؂�ւ�.
		 *
		 * !@param stateName : �؂�ւ��X�e�[�g
		 */
		void ChangeState(StateType stateName);


		/**
		 *  �X�e�[�g�폜.
		 *
		 * !@param stateName : �폜�X�e�[�g
		 */
		void Remove(StateType stateName)
		{
			if (m_stateList.contains(stateName) == false)
			{
				return;
			}
			m_stateList.erase(stateName);
		}

		/**
		 *  �X�e�[�g�S�폜.
		 *
		 */
		void AllRemove()
		{
			m_stateList.clear();
		}

		/**
		 * �X�e�[�g�擾.
		 */
		StatePtr GetState(StateType state)
		{
			if (m_stateList.count(state) == 0) return nullptr;
			return m_stateList[state];
		}

		/**
		 * �X�e�[�g���擾.
		 */
		String GetCurrentStateName() const noexcept { return m_currentName; }
		String GetBeforeName() const noexcept { return m_beforeName; }

	private:
		StateContainer m_stateList;
		StatePtr m_currentState = nullptr;
		String m_currentName;
		String m_beforeName;
	};
}