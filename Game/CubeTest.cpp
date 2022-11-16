#include "CubeTest.h"

void CubeTest::Setting()
{
	AddComponent<MeshRenderer>();
	GetComponent<MeshRenderer>()->SetMesh(MeshManager::GetInstance()->GetStaticMesh(TEXT("Terrain")));

}
