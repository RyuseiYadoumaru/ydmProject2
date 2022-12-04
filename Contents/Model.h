//*****************************************************************************
//* @file   Model.h
//* @brief  
//* @note   モデルデータを管理する
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
		using MeshContainer	= Vector<SharedPtr<Mesh>>;

	public:
		enum class Geometry
		{
			Cube,
			Sphare,
			Terrain
		};
	public:
		void Load(const aiNode* assimpNode, const aiScene* assimpScene);
		void LoadGeometry(Geometry type);
		void Releace();

	public:
		// メッシュ
		const SharedPtr<Mesh> GetMeshData(uInt32 index) noexcept;
		uInt32 GetMeshNum() const noexcept { return m_meshNum; }
		bool HasMesh() const noexcept { return m_hasMesh; }
		
	public:
		explicit Model(ModelData* parent) : m_parent(parent) {}
		~Model() = default;

	private:
		// 親データ
		ModelData* m_parent = nullptr;

		// メッシュデータ
		MeshContainer m_meshDataList;

		T_String m_name;
		uInt32 m_meshNum = 0;
		bool m_hasMesh = false;

	private:
		static constexpr Float32 m_geometrySize = 50.0f;


	};
}
