//*****************************************************************************
//* @file   SkinnedMeshRenderer.h
//* @brief  
//* @note   ボーンアニメーションつきのメッシュを描画を行うコンポーネント
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

class Texture;
class Animation;
class AnimationClip;
class BlendAnimation;

#define ANIM_BLEND


namespace GAME_SYSTEMS
{
	class Material;
	//class Mesh;
	class Skeleton;
	class Transform;

	class SkinnedMeshRenderer : public Graphics
	{
	public:
		Float32 m_blendParam = 0.0f;

	private:
		SharedPtr<Transform> m_ownerTransform;

		// 仮おき
		SharedPtr<Material> m_material = nullptr;
		SharedPtr<Texture> m_texture = nullptr;

		SharedPtr<SkeletalMesh> m_mesh = nullptr;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		SkinnedMeshRenderer() : Graphics("SkinnedMeshRenderer", Graphics::Type::MeshRenderer) {}
		~SkinnedMeshRenderer() = default;
	};

}