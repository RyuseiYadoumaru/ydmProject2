//*****************************************************************************
//* @file   MeshRenderer.h
//* @brief  
//* @note   ���b�V���̕`����s�����߂̃R���|�[�l���g
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "../System/DX11Mesh.h"
#include "../dx11mathutil.h"
#include "macro.h"
#include "std.h"
#include "Graphics.h"

class Animation;
class AnimationClip;

namespace GAME_SYSTEMS
{
	class Model;
	class Material;
	class Texture;
	class Mesh;
	class Skeleton;
	class Transform;

	class MeshRenderer : public Graphics
	{
		// �`��Ŏg�p���钸�_���
		struct Vertex
		{
			DirectX::XMFLOAT3 Position	= { 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT4 Color		= { 1.0f, 1.0f, 1.0f, 1.0f };
			DirectX::XMFLOAT2 Texcoord	= { 0.0f, 0.0f };
			DirectX::XMFLOAT3 Normal	= { 0.0f, 0.0f, 0.0f };
		};
		// �`��p���b�V��
		using RenderMesh = SYSTEMS::DX11Mesh<MeshRenderer::Vertex>;

	public:
		// ���b�V��
		void SetMesh(SharedPtr<Model> mesh) noexcept { m_mesh = mesh; }
		
		// �}�e���A��
		void SetMaterial(SharedPtr<Material> material) noexcept { m_material = material; }
		SharedPtr<Material> GetMaterial() noexcept;

		void SetUseLitFlag(bool flg) noexcept { m_useLit = flg; }

	private:
		void CreateStaticMesh();
	

	private:
		bool m_useLit = false;

	private:
		SharedPtr<Transform>	m_ownerTransform	= nullptr;
		SharedPtr<Model>		m_mesh				= nullptr;
		SharedPtr<Material>		m_material			= nullptr;

		Vector<UniquePtr<RenderMesh>> m_meshList;


	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		MeshRenderer() : Graphics("MeshRenderer", Graphics::Type::MeshRenderer) {}
		~MeshRenderer() = default;
	};

}