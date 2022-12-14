#include "DebugCamera.h"
#include "DebugCameraMovement.h"
#include "DeveloperMenu.h"

void DebugCamera::Setting()
{
	auto debugCamera = AddComponent<DebugCameraMovement>();
	debugCamera->SetDebugCamera(this);
	Int32 priority = developer::DeveloperMenu::GetDebugCameraPriority();
	GetComponent<GAME_SYSTEMS::Camera>()->SetPriority(priority);
}
