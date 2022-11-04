#include "TestObject.h"
#include "TestScript.h"
#include "Transform.h"


USING_GAME_SYSTEMS;

void TestObject::Setting()
{
	AddComponent<TestScript>();
	AddComponent<Transform>();
}
