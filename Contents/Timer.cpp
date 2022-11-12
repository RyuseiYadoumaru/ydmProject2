//*****************************************************************************
//* @file   Timer.h
//* @brief  �^�C�}�[�N���X
//* @note   ���Ԏ�����Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Timer.h"
#include "../System/GameSystemManager.h"
#include "../System/Framelate.h"

USING_GAME_SYSTEMS;

const Float32 Timer::DeltaTime() noexcept
{
    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    if (framelate != nullptr) return framelate->GetDeltaTime() * framelate->GetTimeScale();
    else
    {
        tools::Debug::LogError("Framelate����������Ă��܂���");
        return 0.0f;
    }
}

const Float32 Timer::UnScaleDeltaTime() noexcept
{
    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    if (framelate != nullptr) return framelate->GetDeltaTime();
    else
    {
        tools::Debug::LogError("Framelate����������Ă��܂���");
        return 0.0f;
    }
}

const uInt64 Timer::FrameCount() noexcept
{
    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    if (framelate != nullptr) return framelate->GetTotalFrame();
    else
    {
        tools::Debug::LogError("Framelate����������Ă��܂���");
        return 0;
    }
}

const Float64 Timer::TotalTime() noexcept
{

    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    if (framelate != nullptr) return framelate->GetGameTotalTime();
    else
    {
        tools::Debug::LogError("Framelate����������Ă��܂���");
        return 0.0f;
    }
}

const Float64 Timer::UnScaleTotlaTime() noexcept
{
    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    if (framelate != nullptr) return framelate->GetTotalTime();
    else
    {
        tools::Debug::LogError("Framelate����������Ă��܂���");
        return 0.0f;
    }
}

void Timer::SetTimeScale(Float32 setScale) noexcept
{
    /** �^�C���X�P�[����� */
    if (setScale > m_maxTimeScale) setScale = m_maxTimeScale;

    /** �^�C���X�P�[������ */
    if (setScale < m_minTimeScale) setScale = m_minTimeScale;
    
    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    if (framelate != nullptr) return framelate->SetTimeScale(setScale);
    else tools::Debug::LogError("Framelate����������Ă��܂���");

}

const Float32 Timer::TimeScale() noexcept
{
    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    if (framelate != nullptr) return framelate->GetTimeScale();
    else
    {
        tools::Debug::LogError("Framelate����������Ă��܂���");
        return 0.0f;
    }
}

const bool Timer::GetIsFixed() noexcept
{
    auto framelate = GameSystemManager::GetInstance()->GetSubSystem<Framelate>("Framelate");
    return framelate->GetFixed();
}