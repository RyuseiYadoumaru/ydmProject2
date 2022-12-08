//*****************************************************************************
//* @file   Statemachine.h
//* @brief  ステートマシーンの基底クラス
//* @note   FSM (FiniteStateMachine) : 有限状態機械
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
		 *  ステート登録.
		 *
		 * !@param stateName : ステート
		 * !@param state	 : ステートクラス
		 */
		void Register(StateType stateName, StatePtr state) noexcept
		{
			m_stateList.insert(std::make_pair(stateName, state));
		}

		/**
		 *  ステート切り替え.
		 *
		 * !@param stateName : 切り替えステート
		 */
		void ChangeState(StateType stateName);


		/**
		 *  ステート削除.
		 *
		 * !@param stateName : 削除ステート
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
		 *  ステート全削除.
		 *
		 */
		void AllRemove()
		{
			m_stateList.clear();
		}

		/**
		 * ステート取得.
		 */
		StatePtr GetState(StateType state)
		{
			if (m_stateList.count(state) == 0) return nullptr;
			return m_stateList[state];
		}

		/**
		 * ステート名取得.
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