#include "DebugCamera.h"
#include "DebugCameraMovement.h"

void DebugCamera::Setting()
{
	auto debugCamera = AddComponent<DebugCameraMovement>();
	debugCamera->SetDebugCamera(this);
	GetComponent<GAME_SYSTEMS::Camera>()->SetPriority(5);
}
