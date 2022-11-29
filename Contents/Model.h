//*****************************************************************************
//* @file   Model.h
//* @brief  
//* @note   ���f���f�[�^���Ǘ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"


struct aiScene;
struct aiNode;

namespace GAME_SYSTEMS
{
	class ModelData;
	class Mesh;

	class Model
	{
		enum class Geometry
		{
			Cube,
			Sphare,
			Terrain
		};
		using MeshContainer	= Vector<SharedPtr<Mesh>>;

	public:
		void Load(const aiNode* assimpNode, const aiScene* assimpScene);
		void LoadGeometry(Geometry type);
		void Releace();

	public:
		// ���b�V��
		const SharedPtr<Mesh>& GetMeshData(uInt32 index) noexcept;
		uInt32 GetMeshNum() const noexcept { return m_meshNum; }
		bool HasMesh() const noexcept { return m_hasMesh; }
		
	public:
		explicit Model(ModelData* parent) : m_parent(parent) {}
		~Model() = default;

	private:
		void CreateCube();
		void CreateSphare();
		void CreateTerrain();

	private:
		// �e�f�[�^
		ModelData* m_parent = nullptr;

		// ���b�V���f�[�^
		MeshContainer m_meshDataList;

		T_String m_name;
		uInt32 m_meshNum = 0;
		bool m_hasMesh = false;


	};
}
