#include "DefaultCamera.h"

void GAME_SYSTEMS::DefaultCamera::SetUp()
{
	m_transform = AddComponent<Transform>();
	AddComponent<Camera>();
	m_tag = Tag::Camera;
	Setting();
}

void GAME_SYSTEMS::DefaultCamera::Setting()
{
}
