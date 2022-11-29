////*****************************************************************************
////* @file   StaticMesh.h
////* @brief  
////* @note   �Î~���Ă��郁�b�V���I�u�W�F�N�g
////* 
////* @author YadoumaruRyusei
////* @date   November 2022
////*****************************************************************************
//#pragma once
//#include "MeshHeader.h"
//
//namespace GAME_SYSTEMS
//{
//	class Material;
//	class StaticMesh : public Mesh
//	{
//	protected:
//		struct Vertex
//		{
//			DirectX::XMFLOAT3 Position	= { 0.0f, 0.0f, 0.0f };
//			DirectX::XMFLOAT4 Color		= { 1.0f, 1.0f, 1.0f, 1.0f };
//			DirectX::XMFLOAT2 Texcoord	= { 0.0f, 0.0f };
//			DirectX::XMFLOAT3 Normal	= { 0.0f, 0.0f, 0.0f };
//		};
//	public:
//		SharedPtr<Material> GetMaterial() const noexcept { return m_material; }
//
//		virtual void Load(T_String meshName) override;
//		virtual void Releace() override;
//		virtual void Render() override;
//
//	public:
//		StaticMesh& operator=(const StaticMesh& staticMesh) noexcept;
//	protected:
//		Vector<Polygon<StaticMesh::Vertex>> m_meshList;
//		SharedPtr<Material> m_material = nullptr;
//	
//	private:
//		// �}�e���A���擾
//		void LoadMaterial();
//
//		// �m�[�h���
//		void ProcessNode(aiNode* node, AssimpScene* assimpScene);
//		// ���b�V�����
//		Polygon<StaticMesh::Vertex> ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, Int32 meshidx);
//
//	};
//}
