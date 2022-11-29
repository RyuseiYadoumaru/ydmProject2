//*****************************************************************************
//* @file   SkinnedMeshRenderer.h
//* @brief  
//* @note   �{�[���A�j���[�V�������̃��b�V����`����s���R���|�[�l���g
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
class BlendAnimation;

#define ANIM_BLEND


namespace GAME_SYSTEMS
{
	class Model;
	class Material;
	class Texture;
	class Mesh;
	class Skeleton;
	class Transform;
	
	class SkinnedMeshRenderer : public Graphics
	{
		// �`��Ŏg�p���钸�_���
		struct Vertex
		{
			DirectX::XMFLOAT3 Position	= { 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT3 Normal	= { 0.0f, 0.0f, 0.0f };			
			DirectX::XMFLOAT2 Texcoord	= { 0.0f, 0.0f };
			Int32	BoneIndex[4]		= { -1, -1, -1, -1 };			
			Float32	BoneWeight[4]		= { 0.0f, 0.0f, 0.0f, 0.0f };	
			Int32	BoneNum				= 0;							
		};

		// �`��p���b�V��
		using RenderMesh = SYSTEMS::DX11Mesh<SkinnedMeshRenderer::Vertex>;

	public:
		// ���b�V��
		void SetMesh(SharedPtr<Model> mesh) noexcept { m_mesh = mesh; }

		// �}�e���A��
		void SetMaterial(SharedPtr<Material> mat) noexcept { m_material = mat; }
		SharedPtr<Material> GetMaterial() noexcept;

		// �X�P���g��
		void SetSkeleton(SharedPtr<Skeleton> skeleton) noexcept { m_skeleton = skeleton; }
		SharedPtr<Skeleton> GetSkeleton() const noexcept { return m_skeleton; }

	private:
		void CreateSkeletonMesh();

	private:
		SharedPtr<Transform> m_ownerTransform	= nullptr;
		SharedPtr<Model>	 m_mesh				= nullptr;
		SharedPtr<Skeleton>	 m_skeleton			= nullptr;
		SharedPtr<Material>	 m_material			= nullptr;

		Vector<UniquePtr<RenderMesh>> m_meshList;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		SkinnedMeshRenderer() : Graphics("SkinnedMeshRenderer", Graphics::Type::SkinnedMeshRenderer) {}
		~SkinnedMeshRenderer() = default;
	};

}