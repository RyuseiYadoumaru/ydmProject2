//*****************************************************************************
//* @file   Mesh.h
//* @brief  
//* @note   ���b�V���ɕK�v�ȏ����Ǘ�����
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

		// ���O
		T_String GetMeshName() const noexcept { return m_meshName; }

		// ���_
		const Vector<SharedPtr<SYSTEMS::VertexData>>& GetVertexData() const noexcept { return m_vertexDataList; }
		uInt32 GetVertexNum() const noexcept { return m_vertexNum; }

		// �t�F�[�X
		const Vector<SharedPtr<SYSTEMS::Face>>& GetFaceData() const noexcept { return m_faceList; }

		// �{�[�����
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


