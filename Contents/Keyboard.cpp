//******************************************************************************
//* @file   Keyboard.cpp
//* @brief  キーボード
//* @note   キーボード入力を管理する
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Keyboard.h"
#include "../System/GameSystemManager.h"
#include "../System/KeyboardSystem.h"

bool GAME_SYSTEMS::Keyboard::Press(Keycode input)
{
	auto keySystem = GameSystemManager::GetInstance()->GetSubSystem<KeyboardSystem>("KeyboardSystem");
	Byte buffer = static_cast<Byte>(input);
	Byte key = keySystem->GetKeyBuffer(buffer);
	return key & keySystem->m_MaskInputKeyboardBuffer ? true : false;
}


bool GAME_SYSTEMS::Keyboard::Releace(Keycode input)
{
	auto keySystem = GameSystemManager::GetInstance()->GetSubSystem<KeyboardSystem>("KeyboardSystem");
	Byte buffer = static_cast<Byte>(input);
	Byte key = keySystem->GetKeyBuffer(buffer);
	Byte old = keySystem->GetOldKeyBuffer(buffer);
	return ((key ^ old & key ) & keySystem->m_MaskInputKeyboardBuffer) ? true : false;
}


bool GAME_SYSTEMS::Keyboard::Trigger(Keycode input)
{
	auto keySystem = GameSystemManager::GetInstance()->GetSubSystem<KeyboardSystem>("KeyboardSystem");
	Byte buffer = static_cast<Byte>(input);
	Byte key = keySystem->GetKeyBuffer(buffer);
	Byte old = keySystem->GetOldKeyBuffer(buffer);
	return ((key ^ old & key) & keySystem->m_MaskInputKeyboardBuffer) ? true : false;
}