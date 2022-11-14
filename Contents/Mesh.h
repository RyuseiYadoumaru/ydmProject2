#pragma once
#include "Polygon.h"
#include <d3d11.h>

class AssimpScene;
struct aiNode;
struct aiMesh;

// メッシュのデータクラス
namespace GAME_SYSTEMS
{
	class Mesh
	{
	public:
		void Load(AssimpScene* assimpScene); // 読み込み
		void LoadCube();
		void Unload();
		void Draw();

	private:
		// ノード解析
		void ProcessNode(aiNode* node, AssimpScene* assimpScene);
		// メッシュ解析
		Polygon ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, int meshidx);

	private:
		Vector<Polygon> m_meshes;

	};
}


