#include "Editor.h"
#include "../ThirdParty/Imgui/imgui.h"
#include "../ThirdParty/Imgui/imgui_impl_dx11.h"
#include "../ThirdParty/Imgui/imgui_impl_win32.h"

void SYSTEMS::Editor::Initialize()
{
}

void SYSTEMS::Editor::Render()
{
	ImGui::SetNextWindowPos(ImVec2(m_position.x, m_position.y));
	ImGui::SetNextWindowSize(ImVec2(m_size.x, m_size.y));
	ImGui::Begin(m_windowName.c_str());

	Update();

	ImGui::End();
}
