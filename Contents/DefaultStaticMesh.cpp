//#include "DefaultStaticMesh.h"
//#include "Material.h"
//#include "myMath.h"
//
//void GAME_SYSTEMS::DefaultStaticMesh::Load(T_String meshName)
//{
//	if (meshName == CUBE)
//	{
//		CreateCube();
//	}
//	else if (meshName == SPHERE)
//	{
//		CreateSphere();
//	}
//	else if (meshName == TERRAIN)
//	{
//		CreateTerrain();
//	}
//	else
//	{
//		CreateCube();
//	}
//
//	m_material = std::make_shared<Material>();
//	m_material->LoadShader(TEXT("DefaultMeshVertexShader"), TEXT("UnlitDefaultPixelShader"));
//}
//
//void GAME_SYSTEMS::DefaultStaticMesh::Render()
//{
//	auto directX = SYSTEMS::DirectXGraphics::GetInstance();
//	for (auto& polygon : m_meshList)
//	{
//		polygon.Draw(&directX->GetImmediateContext());
//	}
//}
//
//void GAME_SYSTEMS::DefaultStaticMesh::CreateCube()
//{
//	//Face face[12];
//	//// インデックス生成
//	//face[0].idx[0] = 0;		// 手前  ok
//	//face[0].idx[1] = 1;
//	//face[0].idx[2] = 2;
//
//	//face[1].idx[0] = 2;
//	//face[1].idx[1] = 3;
//	//face[1].idx[2] = 0;
//
//	//face[2].idx[0] = 5;		// 奥  ok
//	//face[2].idx[1] = 4;
//	//face[2].idx[2] = 7;
//
//	//face[3].idx[0] = 7;
//	//face[3].idx[1] = 6;
//	//face[3].idx[2] = 5;
//
//	//face[4].idx[0] = 4;		// 左側 ok
//	//face[4].idx[1] = 0;
//	//face[4].idx[2] = 7;
//
//	//face[5].idx[0] = 0;
//	//face[5].idx[1] = 3;
//	//face[5].idx[2] = 7;
//
//	//face[6].idx[0] = 1;		// 右側 ok
//	//face[6].idx[1] = 5;
//	//face[6].idx[2] = 6;
//
//	//face[7].idx[0] = 1;
//	//face[7].idx[1] = 6;
//	//face[7].idx[2] = 2;
//
//	//face[8].idx[0] = 0;		// 上側 ok
//	//face[8].idx[1] = 4;
//	//face[8].idx[2] = 1;
//
//	//face[9].idx[0] = 4;
//	//face[9].idx[1] = 5;
//	//face[9].idx[2] = 1;
//
//	//face[10].idx[0] = 3;		// 下側
//	//face[10].idx[1] = 2;
//	//face[10].idx[2] = 7;
//
//	//face[11].idx[0] = 6;
//	//face[11].idx[1] = 7;
//	//face[11].idx[2] = 2;
//
//	//Vector<uInt32> indexList;
//	//for (auto& f : face)
//	//{
//	//	for (Int32 i = 0; i < 3; i++)
//	//	{
//	//		indexList.push_back(f.idx[i]);
//	//	}
//	//}
//
//	//// 頂点生成
//	//Vector<Vertex> vertex;
//	//vertex[0].Position.x = -(m_lengthx / 2.0f);
//	//vertex[0].Position.y = (m_lengthy / 2.0f);
//	//vertex[0].Position.z = -(m_lengthz / 2.0f);
//
//	//vertex[1].Position.x = (m_lengthx / 2.0f);
//	//vertex[1].Position.y = (m_lengthy / 2.0f);
//	//vertex[1].Position.z = -(m_lengthz / 2.0f);
//
//	//vertex[2].Position.x = (m_lengthx / 2.0f);
//	//vertex[2].Position.y = -(m_lengthy / 2.0f);
//	//vertex[2].Position.z = -(m_lengthz / 2.0f);
//
//	//vertex[3].Position.x = -(m_lengthx / 2.0f);
//	//vertex[3].Position.y = -(m_lengthy / 2.0f);
//	//vertex[3].Position.z = -(m_lengthz / 2.0f);
//
//	//vertex[4].Position.x = -(m_lengthx / 2.0f);
//	//vertex[4].Position.y = (m_lengthy / 2.0f);
//	//vertex[4].Position.z = (m_lengthz / 2.0f);
//
//	//vertex[5].Position.x = (m_lengthx / 2.0f);
//	//vertex[5].Position.y = (m_lengthy / 2.0f);
//	//vertex[5].Position.z = (m_lengthz / 2.0f);
//
//	//vertex[6].Position.x = (m_lengthx / 2.0f);
//	//vertex[6].Position.y = -(m_lengthy / 2.0f);
//	//vertex[6].Position.z = (m_lengthz / 2.0f);
//
//	//vertex[7].Position.x = -(m_lengthx / 2.0f);
//	//vertex[7].Position.y = -(m_lengthy / 2.0f);
//	//vertex[7].Position.z = (m_lengthz / 2.0f);
//
//	//for (int i = 0; i < 8; i++) {
//	//	m_vertex[i].Color = m_color;
//	//}
//}
//
//void GAME_SYSTEMS::DefaultStaticMesh::CreateSphere()
//{
//	// インデックス生成
//	Vector<Face> face;
//	for (uInt32 y = 0; y < m_divisionVertical; y++)
//	{
//		for (uInt32 x = 0; x < m_divisionHorizontal; x++)
//		{
//			Int32 count = (m_divisionHorizontal + 1) * y + x;			// 左上座標のインデックス
//
//			Face f;
//			// 上半分
//			f.idx[0] = count;
//			f.idx[1] = count + 1;
//			f.idx[2] = count + 1 + (m_divisionHorizontal + 1);
//
//			face.emplace_back(f);
//
//			// 下半分
//			f.idx[0] = count;
//			f.idx[1] = count + (m_divisionHorizontal + 1) + 1;
//			f.idx[2] = count + (m_divisionHorizontal + 1);
//
//			face.emplace_back(f);
//
//		}
//	}
//
//	Vector<uInt32> indexList;
//	for (auto& f : face)
//	{
//		for (Int32 i = 0; i < 3; i++)
//		{
//			indexList.push_back(f.idx[i]);
//		}
//	}
//
//
//	// 頂点
//	Vector<StaticMesh::Vertex> vertex;
//
//	// 方位角と仰角から球メッシュの頂点データを作成
//	for (uInt32 y = 0; y <= m_divisionVertical; y++) 
//	{
//		// 仰角をセット
//		Float32 elevation = (DirectX::XM_PI * (Float32)y) / (Float32)m_divisionVertical;
//		
//		// 仰角に応じた半径を計算
//		Float32 r = m_radius * sinf(elevation);
//
//		for (uInt32 x = 0; x <= m_divisionHorizontal; x++)
//		{
//			Float32 azimuth = (2.0f * DirectX::XM_PI * (Float32)x) / (Float32)m_divisionHorizontal;	// 方位角をセット
//
//			Vertex v;
//			v.Position.x = r * cosf(azimuth);
//			v.Position.y = m_radius * cosf(elevation);
//			v.Position.z = r * sinf(azimuth);
//
//			// 法線をセット
//			//Normalize(v.Position, Normal); // 法線を計算
//			v.Normal = v.Position;
//
//			v.Color = { 0.9f, 0.1f, 0.1f, 1.0f };				// 頂点カラー
//
//			vertex.emplace_back(v);
//		}
//	}
//
//	m_meshList.push_back(Polygon<StaticMesh::Vertex>(vertex, indexList));
//}
//
//void GAME_SYSTEMS::DefaultStaticMesh::CreateTerrain()
//{
//	Float32 meshSize = m_polygonSize * 2.0f;
//	Vector<StaticMesh::Vertex> vertexList;
//
//
//	for (uInt32 y = 0; y < m_terrainSizeY; y++)
//	{
//		Float32 meshOffsetY = meshSize * y;
//		for (uInt32 x = 0; x < m_terrainSizeX; x++)
//		{
//			Vector<StaticMesh::Vertex> addVertex(6);
//			Float32 meshOffsetX = meshSize * x;
//			addVertex[0].Position = { -m_polygonSize + meshOffsetX, 0.0f,  m_polygonSize + meshOffsetY };
//			addVertex[1].Position = { -m_polygonSize + meshOffsetX, 0.0f, -m_polygonSize + meshOffsetY };
//			addVertex[2].Position = {  m_polygonSize + meshOffsetX, 0.0f, -m_polygonSize + meshOffsetY };
//			addVertex[3].Position = {  m_polygonSize + meshOffsetX, 0.0f,  m_polygonSize + meshOffsetY };
//			addVertex[4].Position = { -m_polygonSize + meshOffsetX, 0.0f,  m_polygonSize + meshOffsetY };
//			addVertex[5].Position = {  m_polygonSize + meshOffsetX, 0.0f, -m_polygonSize + meshOffsetY };
//
//			addVertex[0].Texcoord = { 0.0f,0.0f };
//			addVertex[1].Texcoord = { 0.0f,1.0f };
//			addVertex[2].Texcoord = { 1.0f,1.0f };
//			addVertex[3].Texcoord = { 1.0f,0.0f };
//			addVertex[4].Texcoord = { 0.0f,0.0f };
//			addVertex[5].Texcoord = { 1.0f,1.0f };
//
//			for (auto& addV : addVertex)
//			{
//				vertexList.push_back(addV);
//			}
//		}
//	}
//	Vector<uInt32> indexList;
//	uInt32 counter = -1;
//	for (auto& v : vertexList)
//	{
//		counter++;
//		v.Normal = v.Position;
//		indexList.push_back(counter);
//
//	}
//	m_meshList.push_back(Polygon<StaticMesh::Vertex>(vertexList, indexList));
//}
