//*****************************************************************************
//* @file   KeyboardSystem.h
//* @brief  �L�[�{�[�h�V�X�e��
//* @note   �L�[���͎���̍X�V���s��
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include "KeyboardSystem.h"
#include "Inputsystem.h"
#include "Debug.h"

bool GAME_SYSTEMS::KeyboardSystem::Initialize()
{
    return true;
}

/**
 *  �L�[�{�[�h���͂̍X�V.
 * 
 * !@return 
 */
bool GAME_SYSTEMS::KeyboardSystem::Run()
{
    /** �f�o�C�X�F�� */
    HRESULT hr;
    auto directKeyboard = systems::Inputsystem::GetInstance()->GetDirectKeyboard();
    hr = directKeyboard->Acquire();


    /** ���͏�ԕۑ� */
    memcpy(&m_oldKeyBuffer, m_keyBuffer, sizeof(m_keyBuffer));
    hr = directKeyboard->GetDeviceState(sizeof(m_keyBuffer), (LPVOID)&m_keyBuffer);

    if (hr == DIERR_INPUTLOST)
    {
        // �f�o�C�X�ĔF��
        directKeyboard->Acquire();
        return false;
    }
    return true;
}

bool GAME_SYSTEMS::KeyboardSystem::Finalize()
{
    return true;
}
