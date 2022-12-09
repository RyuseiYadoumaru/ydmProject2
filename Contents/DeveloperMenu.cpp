//*****************************************************************************
//* @file   DeveloperMenu.cpp
//* @brief  
//* @note   開発者用メニュー
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#include "DeveloperMenu.h"
#include "Line.h"

USING_GAME_SYSTEMS;
using namespace developer;

DeveloperMenu::Type DeveloperMenu::m_type = DeveloperMenu::Type::Master;
SharedPtr<GAME_SYSTEMS::Line> DeveloperMenu::m_debugLine = nullptr;


void developer::DeveloperMenu::SetUp()
{
    m_debugLine = std::make_shared<Line>();
    Vector<Line::Vertex> v;
    v.resize(2);
    v[0].Position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    v[1].Position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    v[0].Color    = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    v[1].Color    = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    m_debugLine->Load(v);
}

void developer::DeveloperMenu::ShutDown()
{
    m_debugLine->Releace();
    m_debugLine = nullptr;
}

void developer::DeveloperMenu::ChangeType(DeveloperMenu::Type type) noexcept
{
#if _DEBUG
    m_type = type;
#else
    m_type = DeveloperMenu::Type::Master;
#endif
}
