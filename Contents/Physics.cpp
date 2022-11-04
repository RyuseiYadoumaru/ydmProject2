#include "Physics.h"

USING_GAME_SYSTEMS;
Map<Physics::Type, Unordered_Map<uInt32, Physics*>> Physics::m_physicsList;

bool GAME_SYSTEMS::Physics::PhysicsUpdate()
{
    for (auto& physicsStage : m_physicsList)
    {
        for (auto& physics : physicsStage.second)
        {
            physics.second->Update();
        }
    }
    return true;
}

bool GAME_SYSTEMS::Physics::PhysicsReleace()
{
    m_physicsList.clear();
    return true;
}

void GAME_SYSTEMS::Physics::Initialize()
{
    m_physicsList[m_type][m_id] = this;
}

void GAME_SYSTEMS::Physics::Finalize()
{
    m_physicsList[m_type].erase(m_id);
}
