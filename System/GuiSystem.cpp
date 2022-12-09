//*****************************************************************************
//* @file   GuiSystem.cpp
//* @brief  GUIのシステム
//* @note   GUIの設定周りを行う
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************

#include "GuiSystem.h"
#include "EditorManager.h"
#include "Core/Editor.h"
#include "ThirdParty/Imgui/imgui.h"
#include "ThirdParty/Imgui/imgui_impl_dx11.h"
#include "ThirdParty/Imgui/imgui_impl_win32.h"
#include "DirectXGraphics.h"
#include "MessageWindow.h"
#include "Window.h"
#include "Debug.h"


#include "../Editor/TestEditor.h"
USING_EDITOR_SYSTEMS;

/**
 *  初期化.
 * 
 * !@return true : 正常終了
 */
bool systems::GuiSystem::SetUp()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplWin32_Init(Window::GetInstance()->GetHandle());
    auto& device = DirectXGraphics::GetInstance()->GetDevice();
    auto& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
    if (ImGui_ImplDX11_Init(&device, &deviceContext) == false)
    {
        tools::Debug::LogError("Guiの初期化に失敗しました");
        return false;
    }
    return true;
}

/**
 *  終了処理.
 * 
 * !@return true : 正常終了
 */
bool systems::GuiSystem::ShutDown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return true;
}

bool systems::GuiSystem::Run()
{
    auto editorManager = EditorManager::GetInstance();
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    for (auto& editor : editorManager->m_editorList)
    {
        editor.second->Render();
    }
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return true;
}

void systems::GuiSystem::EditorSetUp()
{
    EditorManager::GetInstance()->Create<TestEditor>(TEXT("TestEdit"), 0.0f, 0.0f);
}
