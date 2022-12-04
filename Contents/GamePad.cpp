//*****************************************************************************
//* @file   GamePad.cpp
//* @brief  
//* @note   ゲームパッドの入力を管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "GamePad.h"
#include "../System/GameSystemManager.h"
#include "../System/GamePadSystem.h"


USING_GAME_SYSTEMS;
USING_MY_MATH;

bool GAME_SYSTEMS::GamePad::Press(Xinput input, uInt32 index)
{
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    return (pad->GetXinputState(index).Gamepad.wButtons & static_cast<uInt32>(input));
}

bool GAME_SYSTEMS::GamePad::Trigger(Xinput input, uInt32 index)
{
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    bool padState = (pad->GetXinputState(index).Gamepad.wButtons & static_cast<uInt32>(input)) != 0;
    bool oldPadState = (pad->GetOldXinputState(index).Gamepad.wButtons & static_cast<uInt32>(input)) == 0;
    return padState && oldPadState;
}

bool GAME_SYSTEMS::GamePad::Releace(Xinput input, uInt32 index)
{
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    bool padState = (pad->GetXinputState(index).Gamepad.wButtons & static_cast<uInt32>(input)) == 0;
    bool oldPadState = (pad->GetOldXinputState(index).Gamepad.wButtons & static_cast<uInt32>(input)) != 0;
    return padState && oldPadState;
}

myMath::Vector2 GAME_SYSTEMS::GamePad::LeftStick(uInt32 index)
{
    Vector2 stick = { 0.0f, 0.0f };
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    stick.x = pad->GetXinputState(index).Gamepad.sThumbLX / m_stickMax;
    stick.y = pad->GetXinputState(index).Gamepad.sThumbLY / m_stickMax;
    return stick;
}

myMath::Vector2 GAME_SYSTEMS::GamePad::RightStick(uInt32 index)
{
    Vector2 stick = { 0.0f, 0.0f };;
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    stick.x = pad->GetXinputState(index).Gamepad.sThumbRX / m_stickMax;
    stick.y = pad->GetXinputState(index).Gamepad.sThumbRY / m_stickMax;
    return stick;
}

Float32 GAME_SYSTEMS::GamePad::LeftTrigger(uInt32 index)
{
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    Float32 param = pad->GetXinputState(index).Gamepad.bLeftTrigger;
    return param / m_triggerMax;
}

Float32 GAME_SYSTEMS::GamePad::RightTrigger(uInt32 index)
{
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    Float32 param = pad->GetXinputState(index).Gamepad.bRightTrigger;
    return param / m_triggerMax;
}

Float32 GAME_SYSTEMS::GamePad::OldLeftTrigger(uInt32 index)
{
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    Float32 param = pad->GetOldXinputState(index).Gamepad.bLeftTrigger;
    return param / m_triggerMax;
}

Float32 GAME_SYSTEMS::GamePad::OldRightTrigger(uInt32 index)
{
    auto pad = GameSystemManager::GetInstance()->GetSubSystem<GamePadSystem>("GamePadSystem");
    Float32 param = pad->GetOldXinputState(index).Gamepad.bRightTrigger;
    return param / m_triggerMax;
}
