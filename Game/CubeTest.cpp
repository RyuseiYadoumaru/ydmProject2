#include "CubeTest.h"

void CubeTest::Setting()
{
	AddComponent<MeshRenderer>();
	GetComponent<MeshRenderer>()->SetMesh(MeshManager::GetInstance()->GetStaticMesh(TEXT("Terrain")));
	auto mat = GetComponent<MeshRenderer>()->GetMaterial();
	mat->AddTexture(TextureManager::GetInstance()->GetTexture("MeshTexture.png"), 0);
}
