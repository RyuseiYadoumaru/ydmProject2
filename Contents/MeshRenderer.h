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

class Material;
class Texture;
class MeshData;
class Skeleton;
class Animation;
class AnimationClip;

namespace GAME_SYSTEMS
{
	class Transform;

	class MeshRenderer : public Graphics
	{
	private:
		SharedPtr<Transform> m_ownerTransform;

		// 仮おき
		SharedPtr<Material> m_material;
		SharedPtr<Texture> m_texture;
		SharedPtr<MeshData> m_meshData;
		SharedPtr<Skeleton> m_skelton;
		SharedPtr<Animation> m_animation;
		SharedPtr<AnimationClip> m_animClip;
		DirectX::XMFLOAT4X4 m_mtx;;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		MeshRenderer() : Graphics("MeshRenderer", Graphics::Type::MeshRenderer) {}
		~MeshRenderer() = default;
	};

}