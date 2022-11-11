#include "Graphics.h"
USING_GAME_SYSTEMS;

Map<Graphics::Type, Unordered_Map<uInt32, Graphics*>> Graphics::m_graphicsList;


bool GAME_SYSTEMS::Graphics::GraphicsUpdate()
{
    for (auto& graphicsStage : m_graphicsList)
    {
        for (auto& graphics : graphicsStage.second)
        {
            graphics.second->Update();
        }
    }
    return true;
}

bool GAME_SYSTEMS::Graphics::GraphicReset()
{

    return true;
}

bool GAME_SYSTEMS::Graphics::GraphicsReleace()
{
    m_graphicsList.clear();
    return true;
}

void GAME_SYSTEMS::Graphics::Initialize()
{
    m_graphicsList[m_type][m_id] = this;
}

void GAME_SYSTEMS::Graphics::Finalize()
{
    m_graphicsList[m_type].erase(m_id);
}
