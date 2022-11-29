#include "CubeTest.h"

void CubeTest::Setting()
{
	AddComponent<MeshRenderer>();
	//GetComponent<MeshRenderer>()->SetMesh(ResourceManager::GetInstance()->GetStaticMesh(TEXT("Terrain")));
	auto mat = GetComponent<MeshRenderer>()->GetMaterial();
	mat->AddTexture(ResourceManager::GetInstance()->GetTexture("MeshTexture.png"), 0);
}
