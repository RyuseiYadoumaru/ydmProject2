//*****************************************************************************
//* @file   GameObject.h
//* @brief  �Q�[���I�u�W�F�N�g�N���X
//* @note   �Q�[���Ŏg�p����I�u�W�F�N�g�N���X
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include "GameObject.h"


//==============================================================================
//!	@fn		InstanceProcess
//!	@brief	�������̏������v���Z�X
//==============================================================================
void GAME_SYSTEMS::GameObject::InstanceProcess() noexcept
{
	OnEnable();
	Start();
}


//==============================================================================
//!	@fn		Process
//!	@brief	�X�V���̃v���Z�X
//==============================================================================
void GAME_SYSTEMS::GameObject::Process() noexcept
{
	Update();
	//if (Timer::GetIsFixed() == true) FixedUpdate();
}


//==============================================================================
//!	@fn		DestroyProcess
//!	@brief	�j�󎞂̏I���v���Z�X
//==============================================================================
void GAME_SYSTEMS::GameObject::DestroyProcess() noexcept
{
	End();
	OnDisable();
	m_componentList.clear();
}