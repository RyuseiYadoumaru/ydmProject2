#include "TestEditor.h"
#include "DeveloperMenu.h"

void EDITOR_SYSTEMS::TestEditor::Update()
{
	auto type = DEVELOPER::DeveloperMenu::GetType();
	if (type == DEVELOPER::DeveloperMenu::Type::Develop)
	{
		ImGui::Text("Develop Mode!");
	}
	else if (type == DEVELOPER::DeveloperMenu::Type::Master)
	{
		ImGui::Text("Master Mode!");
	}

	//ImGui::Checkbox("DevelopMode", &m_isDevelop);

	//if (m_isDevelop == true)
	//{
	//	DEVELOPER::DeveloperMenu::ChangeType(DEVELOPER::DeveloperMenu::Type::Develop);
	//}
	//else
	//{
	//	DEVELOPER::DeveloperMenu::ChangeType(DEVELOPER::DeveloperMenu::Type::Master);
	//}
	
	// インスペクター
	//if (ImGui::TreeNode("Mode Log")) 
	//{
	//	auto type = DEVELOPER::DeveloperMenu::GetType();
	//	if (type == DEVELOPER::DeveloperMenu::Type::Develop)
	//	{
	//		ImGui::Text("Develop Mode!");
	//	}
	//	else if (type == DEVELOPER::DeveloperMenu::Type::Master)
	//	{
	//		ImGui::Text("Master Mode!");
	//	}
	//	ImGui::TreePop();
	//}


}
