#include "MainCamera.h"
#include "ThirdPersonCamera.h"

void MainCamera::Setting()
{
	AddComponent<ThirdPersonCamera>();
}
