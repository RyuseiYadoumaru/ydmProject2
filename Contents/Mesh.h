#pragma once
#include "Polygon.h"
#include <d3d11.h>

class AssimpScene;
struct aiNode;
struct aiMesh;

// ���b�V���̃f�[�^�N���X
namespace GAME_SYSTEMS
{
	class Mesh
	{
	public:
		void Load(AssimpScene* assimpScene); // �ǂݍ���
		void LoadCube();
		void Unload();
		void Draw();

	private:
		// �m�[�h���
		void ProcessNode(aiNode* node, AssimpScene* assimpScene);
		// ���b�V�����
		Polygon ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, int meshidx);

	private:
		Vector<Polygon> m_meshes;

	};
}


