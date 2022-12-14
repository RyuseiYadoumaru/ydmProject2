#include "DebugEditor.h"
#include"../Contents/DeveloperMenu.h"

void EDITOR_SYSTEMS::DebugEditor::Update()
{

	ImGui::InputInt("DebugCameraPriority", &developer::DeveloperMenu::m_debugCameraInfo.Priority);

	auto debugPos = developer::DeveloperMenu::m_debugCameraInfo.Position;
	auto debugRot = developer::DeveloperMenu::m_debugCameraInfo.Rotation;
	Float32 pos[3] = { debugPos.x, debugPos.y, debugPos.z };
	Float32 rot[3] = { debugRot.x, debugRot.y, debugRot.z };
	ImGui::InputFloat3("Position", pos);
	ImGui::InputFloat3("Rotation", rot);

	developer::DeveloperMenu::m_debugCameraInfo.Position.x = pos[0];
	developer::DeveloperMenu::m_debugCameraInfo.Position.y = pos[1];
	developer::DeveloperMenu::m_debugCameraInfo.Position.z = pos[2];

	developer::DeveloperMenu::m_debugCameraInfo.Rotation.x = rot[0];
	developer::DeveloperMenu::m_debugCameraInfo.Rotation.y = rot[1];
	developer::DeveloperMenu::m_debugCameraInfo.Rotation.z = rot[2];
}
