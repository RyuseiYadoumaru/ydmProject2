//*****************************************************************************
//* @file   SkinnedMeshRenderer.h
//* @brief  
//* @note   �{�[���A�j���[�V�������̃��b�V����`����s���R���|�[�l���g
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "Graphics.h"
#include <DirectXMath.h>
#include "../dx11mathutil.h"
#include "SkeletalMesh.h"

class Animation;
class AnimationClip;
class BlendAnimation;

#define ANIM_BLEND


namespace GAME_SYSTEMS
{
	class SkeletalMesh;
	class Material;
	class Texture;
	class Skeleton;
	class Transform;

	class SkinnedMeshRenderer : public Graphics
	{
	public:
		// ���b�V��
		void SetMesh(SharedPtr<SkeletalMesh> mesh) noexcept { m_mesh = mesh; }
		SharedPtr<SkeletalMesh> GetMesh() const noexcept { return m_mesh; }

		// �}�e���A��
		void SetMaterial(SharedPtr<Material> mat) noexcept { m_material = mat; }
		SharedPtr<Material> GetMaterial() noexcept;

		// �X�P���g��
		SharedPtr<Skeleton> GetSkeleton() noexcept;
		
	private:
		SharedPtr<Transform>	m_ownerTransform	= nullptr;
		SharedPtr<SkeletalMesh> m_mesh				= nullptr;
		SharedPtr<Material>		m_material			= nullptr;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		SkinnedMeshRenderer() : Graphics("SkinnedMeshRenderer", Graphics::Type::MeshRenderer) {}
		~SkinnedMeshRenderer() = default;
	};

}