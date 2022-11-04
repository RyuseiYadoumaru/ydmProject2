#include "TestScript.h"
#include "Keyboard.h"
USING_GAME_SYSTEMS;

void TestScript::Start()
{
	printf("テスト初期化\n");
}

void TestScript::Update()
{
	if (Keyboard::Trigger(Keycode::A))
	{
		printf("テスト更新\n");
	}
}

void TestScript::End()
{
	printf("テスト終了\n");
}
