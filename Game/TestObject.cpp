#include "TestObject.h"
#include "TestScript.h"
#include "../Game/PlayerMovement.h"
#include "GameContents.h"


USING_GAME_SYSTEMS;

void TestObject::Setting()
{
	AddComponent<TestScript>();
	AddComponent<SkinnedMeshRenderer>();
	AddComponent<PlayerMovement>();
}
