//*****************************************************************************
//* @file   MeshRenderer.h
//* @brief  
//* @note   メッシュの描画を行うためのコンポーネント
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

class Texture;
class Animation;
class AnimationClip;

namespace GAME_SYSTEMS
{
	class Material;
	class Mesh;
	class Skeleton;
	class Transform;

	class MeshRenderer : public Graphics
	{
	public:
		void SetUseLitFlag(bool flg) noexcept { m_useLit = flg; }

	private:
		bool m_useLit = false;

	private:
		SharedPtr<Transform> m_ownerTransform;

		// 仮おき
		SharedPtr<Material> m_material = nullptr;
		SharedPtr<Texture> m_texture = nullptr;
		SharedPtr<Mesh> m_meshData = nullptr;
		SharedPtr<Skeleton> m_skelton = nullptr;
		SharedPtr<Animation> m_animation = nullptr;
		SharedPtr<AnimationClip> m_animClip = nullptr;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		MeshRenderer() : Graphics("MeshRenderer", Graphics::Type::MeshRenderer) {}
		~MeshRenderer() = default;
	};

}