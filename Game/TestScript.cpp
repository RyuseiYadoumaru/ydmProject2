#include "TestScript.h"
#include "Keyboard.h"
USING_GAME_SYSTEMS;

void TestScript::Start()
{
	printf("�e�X�g������\n");
}

void TestScript::Update()
{
	if (Keyboard::Trigger(Keycode::A))
	{
		printf("�e�X�g�X�V\n");
	}
}

void TestScript::End()
{
	printf("�e�X�g�I��\n");
}
