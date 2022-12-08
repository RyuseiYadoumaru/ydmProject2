#include "SphareTest.h"
#include "MoveMentSphere.h"
USING_GAME_SYSTEMS;

void SphareTest::Setting()
{
	AddComponent<MeshRenderer>();
	//GetComponent<MeshRenderer>()->SetMesh(ResourceManager::GetInstance()->GetStaticMesh(TEXT("Sphere")));
	auto mat = GetComponent<MeshRenderer>()->GetMaterial();

	AddComponent<MoveMentSphere>();

	m_transform->m_Scale.Set(1.0f, 1.0f, 1.0f);

}
