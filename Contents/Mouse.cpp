//*****************************************************************************
//* @file   Mouse.cpp
//* @brief  マウス
//* @note   マウスの入力を管理する
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************
#include "Mouse.h"
#include "../System/GameSystemManager.h"
#include "../System/MouseSystem.h"
#include "../System/Window.h"

bool GAME_SYSTEMS::Mouse::Click(MouseCode mouseCode)
{
    auto mouseSystem = GameSystemManager::GetInstance()->GetSubSystem<MouseSystem>("MouseSystem");
    auto mouseState = mouseSystem->GetMouseState();
    return mouseState.rgbButtons[static_cast<int>(mouseCode)] & mouseSystem->m_MaskInputMouseBuffer;
}

bool GAME_SYSTEMS::Mouse::Up(MouseCode mouseCode)
{
    auto mouseSystem = GameSystemManager::GetInstance()->GetSubSystem<MouseSystem>("MouseSystem");
    auto mouseState = mouseSystem->GetMouseState();
    auto oldMouseState = mouseSystem->GetOldMouseState();
    if ((oldMouseState.rgbButtons[static_cast<int>(mouseCode)] & mouseSystem->m_MaskInputMouseBuffer) &&
        !(mouseState.rgbButtons[static_cast<int>(mouseCode)] & mouseSystem->m_MaskInputMouseBuffer))
    {
        return true;
    }
    return false;
}

myMath::Vector2 GAME_SYSTEMS::Mouse::CursorPosition()
{
    POINT cursorPoint;
    GetCursorPos(&cursorPoint);

    auto windowClassName = systems::Window::GetInstance()->GetWindowClassName();
    bool sts = ScreenToClient(FindWindowA(windowClassName.c_str(), nullptr), &cursorPoint);
    if (sts == false)
    {
        tools::Debug::LogError("カーソル座標の取得に失敗しました");
        return myMath::Vector2(0.0f, 0.0f);
    }

    float cursorX = static_cast<Float32>(cursorPoint.x);
    float cursorY = static_cast<Float32>(cursorPoint.y);
    myMath::Vector2 cursorPosition(cursorX, cursorY);
    return cursorPosition;
}

myMath::Vector2 GAME_SYSTEMS::Mouse::CursorVelocity()
{
    auto mouseSystem = GameSystemManager::GetInstance()->GetSubSystem<MouseSystem>("MouseSystem");
    auto mouseState = mouseSystem->GetMouseState();
   
    float velocityX = static_cast<Float32>(mouseState.lX);
    float velocityY = static_cast<Float32>(mouseState.lY);
    myMath::Vector2 velocityPosition(velocityX, velocityY);
    return velocityPosition;
}