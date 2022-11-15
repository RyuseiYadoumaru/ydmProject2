//*****************************************************************************
//* @file   StaticMesh.h
//* @brief  
//* @note   静止しているメッシュオブジェクト
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "MeshHeader.h"

namespace GAME_SYSTEMS
{
	class Material;
	class StaticMesh : public Mesh
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 Position	= { 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT4 Color		= { 255.0f, 255.0f, 255.0f, 255.0f };
			DirectX::XMFLOAT2 Texcoord	= { 0.0f, 0.0f };
			DirectX::XMFLOAT3 Normal	= { 0.0f, 0.0f, 0.0f };
		};
	public:
		virtual void Load(T_String meshName) override;
		virtual void Releace() override;
		virtual void Render() override;

	private:
		// マテリアル取得
		void LoadMaterial();

		// ノード解析
		void ProcessNode(aiNode* node, AssimpScene* assimpScene);
		// メッシュ解析
		Polygon<StaticMesh::Vertex> ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx);

	private:
		Vector<Polygon<StaticMesh::Vertex>> m_meshList;
		SharedPtr<Material> m_material = nullptr;

	};
}
