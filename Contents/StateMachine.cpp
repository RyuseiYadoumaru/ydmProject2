//*****************************************************************************
//* @file   Statemachine.cpp
//* @brief  �X�e�[�g�}�V�[���̊��N���X
//* @note   FSM (FiniteStateMachine) : �L����ԋ@�B
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
	// �S�č폜����
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