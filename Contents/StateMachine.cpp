//*****************************************************************************
//* @file   Statemachine.cpp
//* @brief  ステートマシーンの基底クラス
//* @note   FSM (FiniteStateMachine) : 有限状態機械
//* 
//* @author YadoumaruRyusei
//* @date   October 2022
//*****************************************************************************
#include "StateMachine.h"
#include "StateBase.h"

void GAME_SYSTEMS::StateMachine::Update()
{
	if (m_currentState == nullptr)
	{
		return;
	}
	m_currentState->Update();
}

void GAME_SYSTEMS::StateMachine::End()
{
	// 全て削除する
	AllRemove();
}

void GAME_SYSTEMS::StateMachine::ChangeState(StateType stateName)
{
	if (m_stateList.count(stateName) == 0)
	{
		return;
	}
	if (m_currentState != nullptr)
	{
		m_currentState->ExitState();
		m_beforeName = m_currentName;
	}
	m_currentState = m_stateList[stateName];
	m_currentState->EnterState();
	m_currentName = stateName;
}