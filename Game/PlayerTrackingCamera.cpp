#include "PlayerTrackingCamera.h"
#include "PlayerActionCamera.h"

void PlayerTrackingCamera::Setting()
{
	AddComponent<PlayerActionCamera>();
}
