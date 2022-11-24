#include "Graphics.h"
USING_GAME_SYSTEMS;

Map<Graphics::Type, Unordered_Map<uInt32, Graphics*>> Graphics::m_graphicsList;
Map<Graphics::Type, Unordered_Map<uInt32, Graphics*>> Graphics::m_graphicsInstanceList;


bool GAME_SYSTEMS::Graphics::GraphicsFirstUpdate()
{
    for (auto& instance : m_graphicsInstanceList)
    {
        Type type = instance.first;
        for (auto& i : instance.second)
        {
            uInt32 id = i.first;
            m_graphicsList[type][id] = std::move(i.second);
        }
    }
    m_graphicsInstanceList.clear();
    return true;
}

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
    m_graphicsInstanceList[m_type][m_id] = this;
}

void GAME_SYSTEMS::Graphics::Finalize()
{
    m_graphicsList[m_type].erase(m_id);
}
