//*****************************************************************************
//* @file   GuiSystem.cpp
//* @brief  GUI�̃V�X�e��
//* @note   GUI�̐ݒ������s��
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************

#include "GuiSystem.h"
#include "../ThirdParty/Imgui/imgui.h"
#include "../ThirdParty/Imgui/imgui_impl_dx11.h"
#include "../ThirdParty/Imgui/imgui_impl_win32.h"
#include "DirectXGraphics.h"
#include "MessageWindow.h"
#include "Window.h"
#include "Debug.h"



/**
 *  ������.
 * 
 * !@return true : ����I��
 */
bool systems::GuiSystem::SetUp()
{
#ifdef _DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplWin32_Init(Window::GetInstance()->GetHandle());
    auto& device = DirectXGraphics::GetInstance()->GetDevice();
    auto& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
    if (ImGui_ImplDX11_Init(&device, &deviceContext) == false)
    {
        tools::Debug::LogError("Gui�̏������Ɏ��s���܂���");
        return false;
    }
#endif // _DEBUG
    return true;
}

/**
 *  �I������.
 * 
 * !@return true : ����I��
 */
bool systems::GuiSystem::ShutDown()
{
#ifdef _DEBUG
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#endif // _DEBUG

    return true;
}

void systems::GuiSystem::CreateNewFrame()
{
    //ImGui_ImplWin32_NewFrame();
    //ImGui_ImplDX11_NewFrame();
    //ImGui::NewFrame();
    //bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);

}

/** ������ */
void systems::GuiSystem::Render()
{
    //ImGui::Render();
    //ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
