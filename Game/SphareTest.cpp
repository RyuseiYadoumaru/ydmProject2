#include "SphareTest.h"
#include "MoveMentSphere.h"
USING_GAME_SYSTEMS;

void SphareTest::Setting()
{
	AddComponent<MeshRenderer>();
	GetComponent<MeshRenderer>()->SetMesh(MeshManager::GetInstance()->GetStaticMesh(TEXT("Sphere")));
	auto mat = GetComponent<MeshRenderer>()->GetMaterial();

	AddComponent<MoveMentSphere>();

	m_transform->m_scale.Set(1.0f, 1.0f, 1.0f);

}
