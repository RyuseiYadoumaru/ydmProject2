#include "Editor.h"
#include "../ThirdParty/Imgui/imgui.h"
#include "../ThirdParty/Imgui/imgui_impl_dx11.h"
#include "../ThirdParty/Imgui/imgui_impl_win32.h"

void SYSTEMS::Editor::Initialize()
{
}

void SYSTEMS::Editor::Render()
{
	ImGui::Begin(m_windowName.c_str());

	Update();

	ImGui::End();
}
