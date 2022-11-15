//*****************************************************************************
//* @file   GamePad.cpp
//* @brief  
//* @note   �Q�[���p�b�h�̓��͂��Ǘ�����
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