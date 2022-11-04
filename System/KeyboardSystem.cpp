//*****************************************************************************
//* @file   KeyboardSystem.h
//* @brief  キーボードシステム
//* @note   キー入力周りの更新を行う
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
 *  キーボード入力の更新.
 * 
 * !@return 
 */
bool GAME_SYSTEMS::KeyboardSystem::Run()
{
    /** デバイス認識 */
    HRESULT hr;
    auto directKeyboard = systems::Inputsystem::GetInstance()->GetDirectKeyboard();
    hr = directKeyboard->Acquire();


    /** 入力状態保存 */
    memcpy(&m_oldKeyBuffer, m_keyBuffer, sizeof(m_keyBuffer));
    hr = directKeyboard->GetDeviceState(sizeof(m_keyBuffer), (LPVOID)&m_keyBuffer);

    if (hr == DIERR_INPUTLOST)
    {
        // デバイス再認識
        directKeyboard->Acquire();
        return false;
    }
    return true;
}

bool GAME_SYSTEMS::KeyboardSystem::Finalize()
{
    return true;
}
