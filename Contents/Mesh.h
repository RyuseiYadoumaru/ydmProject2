//*****************************************************************************
//* @file   Mesh.h
//* @brief  
//* @note   メッシュに必要な情報を管理する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "../System/ThirdParty/Assimp/AssimpScene.h"
#include "myMath.h"
#include "macro.h"
#include "std.h"

namespace SYSTEMS
{
	struct VertexData;
	struct Face;
}

namespace GAME_SYSTEMS
{
	class Skeleton;
	class Mesh
	{
	public:
		void Load(const aiMesh* assimpMesh, Skeleton* skeleton);
		void Releace();

		// 名前
		T_String GetMeshName() const noexcept { return m_meshName; }

		// 頂点
		const Vector<SharedPtr<SYSTEMS::VertexData>>& GetVertexData() const noexcept { return m_vertexDataList; }
		uInt32 GetVertexNum() const noexcept { return m_vertexNum; }

		// フェース
		const Vector<SharedPtr<SYSTEMS::Face>>& GetFaceData() const noexcept { return m_faceList; }

		// ボーン情報
		bool HasBone() const noexcept { return m_hasBone; }


	public:
		Mesh() = default;
		~Mesh() = default;

	private:
		T_String m_meshName;

		Vector<SharedPtr<SYSTEMS::VertexData>> m_vertexDataList;
		uInt32 m_vertexNum = 0;

		Vector<SharedPtr<SYSTEMS::Face>> m_faceList;
		uInt32 m_faceNum = 0;

		uInt32 m_boneNum = 0;
		bool m_hasBone = false;

	};
}


