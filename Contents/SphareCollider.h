//*****************************************************************************
//* @file   SphareCollider.h
//* @brief  
//* @note   ���̂̃R���C�_
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
		// ���a
		void SetRadius(Float32 radius) noexcept { m_radius = radius; }
		Float32 GetRadius() const noexcept { return m_radius; }

		// �I�t�Z�b�g
		void SetOffset(Float32 x, Float32 y, Float32 z) noexcept { m_offset.Set(x, y, z); }
		const MY_MATH::Vector3& GetOffset() const noexcept { return m_offset; }

		// �����蔻��
		bool HitCheck(SharedPtr<SphereCollider> collider);

		// �f�o�b�O
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
				DirectX::XMFLOAT4 Color = { 0.1f, 0.9f, 0.0f, 0.3f };
			};
			using RenderMesh = SYSTEMS::DX11Mesh<DebugRenderer::Vertex>;

		public:
			void Initialize();
			void Render();
			void Finalize();

		private:
			Vector<UniquePtr<RenderMesh>> m_meshList;
			SharedPtr<VertexShader>	m_vertexShader	= nullptr;
			SharedPtr<PixelShader>	m_pixelShader	= nullptr;

		};

		//	�f�o�b�O�p�����_�[
		SharedPtr<DebugRenderer> m_debug;

	};
}
