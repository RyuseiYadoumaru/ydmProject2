#include "DefaultStaticMesh.h"
#include "Material.h"

void GAME_SYSTEMS::DefaultStaticMesh::Load(T_String meshName)
{
	if (meshName == CUBE)
	{
		CreateCube();
	}
	else if (meshName == SPHERE)
	{
		CreateSphere();
	}
	else if (meshName == TERRAIN)
	{
		CreateTerrain();
	}
	else
	{
		CreateCube();
	}

	m_material = std::make_shared<Material>();
	m_material->LoadShader(TEXT("DefaultMeshVertexShader"), TEXT("UnlitDefaultPixelShader"));
}

void GAME_SYSTEMS::DefaultStaticMesh::Render()
{
	auto directX = SYSTEMS::DirectXGraphics::GetInstance();
	for (auto& polygon : m_meshList)
	{
		polygon.Draw(&directX->GetImmediateContext());
	}
}

void GAME_SYSTEMS::DefaultStaticMesh::CreateCube()
{
}

void GAME_SYSTEMS::DefaultStaticMesh::CreateSphere()
{
}

void GAME_SYSTEMS::DefaultStaticMesh::CreateTerrain()
{
	Float32 meshSize = m_polygonSize * 2.0f;
	Vector<StaticMesh::Vertex> vertexList;


	for (uInt32 y = 0; y < m_terrainSizeY; y++)
	{
		Float32 meshOffsetY = meshSize * y;
		for (uInt32 x = 0; x < m_terrainSizeX; x++)
		{
			Vector<StaticMesh::Vertex> addVertex(6);
			Float32 meshOffsetX = meshSize * x;
			addVertex[0].Position = { -m_polygonSize + meshOffsetX, 0.0f,  m_polygonSize + meshOffsetY };
			addVertex[1].Position = { -m_polygonSize + meshOffsetX, 0.0f, -m_polygonSize + meshOffsetY };
			addVertex[2].Position = {  m_polygonSize + meshOffsetX, 0.0f, -m_polygonSize + meshOffsetY };
			addVertex[3].Position = {  m_polygonSize + meshOffsetX, 0.0f,  m_polygonSize + meshOffsetY };
			addVertex[4].Position = { -m_polygonSize + meshOffsetX, 0.0f,  m_polygonSize + meshOffsetY };
			addVertex[5].Position = {  m_polygonSize + meshOffsetX, 0.0f, -m_polygonSize + meshOffsetY };

			addVertex[0].Texcoord = { 0.0f,0.0f };
			addVertex[1].Texcoord = { 0.0f,1.0f };
			addVertex[2].Texcoord = { 1.0f,1.0f };
			addVertex[3].Texcoord = { 1.0f,0.0f };
			addVertex[4].Texcoord = { 0.0f,0.0f };
			addVertex[5].Texcoord = { 1.0f,1.0f };

			for (auto& addV : addVertex)
			{
				vertexList.push_back(addV);
			}
		}
	}
	Vector<uInt32> indexList;
	uInt32 counter = -1;
	for (auto& v : vertexList)
	{
		counter++;
		v.Normal = v.Position;
		indexList.push_back(counter);

	}
	m_meshList.push_back(Polygon<StaticMesh::Vertex>(vertexList, indexList));
}
