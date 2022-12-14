#include "DebugEditor.h"
#include "../Contents/DeveloperMenu.h"

void EDITOR_SYSTEMS::DebugEditor::Update()
{
	ImGui::InputInt("DebugCameraPriority", &developer::DeveloperMenu::m_debugCameraInfo.Priority);
}
