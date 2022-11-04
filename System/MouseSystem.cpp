//*****************************************************************************
//* @file   MouseSystem.cpp
//* @brief  マウスシステム
//* @note   マウス入力周りの更新を行う
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************

#include "MouseSystem.h"
#include "Debug.h"
#include "Inputsystem.h"


/**
 *  マウスデバイスの取得を毎フレーム行います .
 * 
 * !@return　true : 正常終了
 */
bool GAME_SYSTEMS::MouseSystem::Initialize()
{
    return true;
}
bool GAME_SYSTEMS::MouseSystem::Run()
{
    HRESULT hr = S_OK;
    auto mouseDevice = systems::Inputsystem::GetInstance()->GetDirectMouse();
    
    // マウス状態取得 
    m_oldMouseState = m_mouseState;
    hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState);
    if (FAILED(hr))
    {
        // デバイスの再認識
        mouseDevice->Acquire();
        return false;
    }

    return true;
}

bool GAME_SYSTEMS::MouseSystem::Finalize()
{
    return true;
}
