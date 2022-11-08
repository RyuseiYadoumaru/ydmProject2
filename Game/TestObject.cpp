#include "TestObject.h"
#include "TestScript.h"
#include "GameContents.h"


USING_GAME_SYSTEMS;

void TestObject::Setting()
{
	AddComponent<TestScript>();
	AddComponent<MeshRenderer>();
}
