//*****************************************************************************
//* @file   SphareCollider.h
//* @brief  
//* @note   球体のコライダ
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "../System/DX11Mesh.h"
#include "macro.h"
#include "std.h"
#include "myMath.h"
#include "Physics.h"

namespace GAME_SYSTEMS
{
	class Transform;
	class Model;
	class VertexShader;
	class PixelShader;
	class SphereCollider : public Physics
	{
	public:
		// 半径
		void SetRadius(Float32 radius) noexcept { m_radius = radius; }
		Float32 GetRadius() const noexcept { return m_radius; }

		// オフセット
		void SetOffset(Float32 x, Float32 y, Float32 z) noexcept { m_offset.Set(x, y, z); }
		const MY_MATH::Vector3& GetOffset() const noexcept { return m_offset; }

		// 当たり判定
		bool HitCheck(SharedPtr<SphereCollider> collider);

		// デバッグ
		void SetIsDebug(bool flg) noexcept { m_isDebug = flg; }

	private:
		MY_MATH::Vector3 m_position;
		MY_MATH::Vector3 m_offset;
		Float32 m_radius;
		bool m_isDebug = false;

	private:
		virtual void Start() override;
		virtual void Update() override;
		virtual void End() override;

	public:
		explicit SphereCollider() :
			Physics("SphereCollider", Type::SphereCollider),
		m_radius(10.0f){}
		SphereCollider(SphereCollider&) = default;
		~SphereCollider() = default;

	private:
		class DebugRenderer
		{
			struct Vertex
			{
				DirectX::XMFLOAT3 Position = { 0.0f, 0.0f, 0.0f };
				DirectX::XMFLOAT4 Color = { 0.2f, 0.9f, 0.0f, 0.3f };
			};
			using RenderMesh = SYSTEMS::DX11Mesh<DebugRenderer::Vertex>;

		public:
			void Initialize(Float32 radius);
			void Render(const MY_MATH::Matrix4x4& mtx);
			void Finalize();

		private:
			UniquePtr<RenderMesh> m_mesh;
			Vector<uInt32> m_indexList;
			SharedPtr<VertexShader>	m_vertexShader	= nullptr;
			SharedPtr<PixelShader>	m_pixelShader	= nullptr;

			constexpr static uInt32 m_division = 20;
		};

		//	デバッグ用レンダー
		SharedPtr<DebugRenderer> m_debug;

	};
}
