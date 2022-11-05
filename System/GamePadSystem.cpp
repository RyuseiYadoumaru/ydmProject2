#include "GamePadSystem.h"

bool GAME_SYSTEMS::GamePadSystem::Initialize()
{
    return true;
}

bool GAME_SYSTEMS::GamePadSystem::Run()
{
    for (int i = 0; i < m_gamePadMaxNum; i++)
    {
        m_oldXinputState[i] = m_xinputState[i];
        XInputGetState(i, &m_xinputState[i]);
    }


    return true;
}

bool GAME_SYSTEMS::GamePadSystem::Finalize()
{
    return true;
}
