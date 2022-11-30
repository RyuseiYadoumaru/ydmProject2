#include "CubeTest.h"

void CubeTest::Setting()
{
	auto mesh = AddComponent<MeshRenderer>();
	mesh->SetMesh(ResourceManager::GetInstance()->GetGeometry(ResourceManager::GeometryType::Terrain));
	auto mat = GetComponent<MeshRenderer>()->GetMaterial();
	mat->AddTexture(ResourceManager::GetInstance()->GetTexture("MeshTexture.png"), 0);
}
