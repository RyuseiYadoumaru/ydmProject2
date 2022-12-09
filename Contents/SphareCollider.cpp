//*****************************************************************************
//* @file   SphareCollider.cpp
//* @brief  
//* @note   ���̂̃R���C�_
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#include "SphareCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ShaderManager.h"
#include "../System/DirectXGraphics.h"
#include "ResourceManager.h"
#include "Model.h"
#include "Mesh.h"
#include "../System/DX11Settransform.h"
#include "DeveloperMenu.h"

bool GAME_SYSTEMS::SphereCollider::HitCheck(SharedPtr<SphereCollider> collider)
{
	//SphereCollider checkCol;
	//checkCol = collider;

	Float32 checkX = (collider->m_position.x - m_position.x);
	Float32 checkY = (collider->m_position.y - m_position.y);
	Float32 checkZ = (collider->m_position.z - m_position.z);
	
	Float32 check = 0.0f;
	check = std::powf(checkX, 2.0f) + std::powf(checkY, 2.0f) + std::powf(checkZ, 2.0f);

	Float32 checkRad = std::powf((collider->m_radius + m_radius), 2.0f);

	if (check <= checkRad)
	{
		return true;
	}
	return false;
}

void GAME_SYSTEMS::SphereCollider::Start()
{
	auto transform = GetOwner()->m_transform;
	m_position = transform->GetPosition();
#ifdef _DEBUG
	m_debug = std::make_shared<DebugRenderer>();
	m_debug->Initialize(m_radius);

#endif
}

void GAME_SYSTEMS::SphereCollider::Update()
{
	auto transform = GetOwner()->m_transform;
	m_position = transform->GetPosition();
	m_position += m_offset;

#ifdef _DEBUG
	if (m_isDebug == true && developer::DeveloperMenu::GetType() == developer::DeveloperMenu::Type::Develop)
	{
		MY_MATH::Matrix4x4 mtx;
		mtx = MY_MATH::Matrix4x4::CreateMatrixIdentity();
		mtx._41 = m_position.x;
		mtx._42 = m_position.y;
		mtx._43 = m_position.z;
		m_debug->Render(mtx);
	}
#endif

}

void GAME_SYSTEMS::SphereCollider::End()
{
#ifdef _DEBUG
	m_debug->Finalize();
#endif
}


void GAME_SYSTEMS::SphereCollider::DebugRenderer::Initialize(Float32 radius)
{
	m_vertexShader = ShaderManager::GetInstance()->GetVertexShader("DebugColliderVertexShader");
	m_pixelShader = ShaderManager::GetInstance()->GetPixelShader("DebugPixelShader");

	// ���̂̃��b�V�������
	// �C���f�b�N�X����a
	for (uInt32 y = 0; y < m_division; y++)
	{
		for (uInt32 x = 0; x < m_division; x++)
		{
			// ������W�̃C���f�b�N�X
			Int32 count = (30 + 1) * y + x;

			Vector<uInt32> f;
			f.resize(3);
			// �㔼��
			f[0] = count;
			f[1] = count + 1;
			f[2] = count + 1 + (m_division + 1);

			for (auto& i : f)
			{
				m_indexList.emplace_back(i);
			}

			// ������
			f[0] = count;
			f[1] = count + (m_division + 1) + 1;
			f[2] = count + (m_division + 1);

			for (auto& i : f)
			{
				m_indexList.emplace_back(i);
			}
		}
	}

	Vector<Vertex> vertexList;
	for (uInt32 y = 0; y <= m_division; y++)
	{
		// �p���Z�b�g
		Float32 elevation = (DirectX::XM_PI * static_cast<Float32>(y)) / static_cast<Float32>(m_division);

		// �p�ɉ��������a���v�Z
		Float32 r = radius * sinf(elevation);

		for (uInt32 x = 0; x <= m_division; x++)
		{
			// ���ʊp���Z�b�g
			Float32 azimuth = (2.0f * DirectX::XM_PI * static_cast<Float32>(x)) /  static_cast<Float32>(m_division);

			Vertex v;
			v.Position.x = r * cosf(azimuth);
			v.Position.y = radius * cosf(elevation);
			v.Position.z = r * sinf(azimuth);

			vertexList.emplace_back(v);
		}
	}

	// �|���S������
	m_mesh = std::make_unique<RenderMesh>(vertexList, m_indexList);
}

void GAME_SYSTEMS::SphereCollider::DebugRenderer::Render(const MY_MATH::Matrix4x4& mtx)
{
	// ���[���h�s������
	MY_MATH::Matrix4x4 world = mtx;
	SYSTEMS::DX11SetTransform::GetInstance()->SetTransform(SYSTEMS::DX11SetTransform::TYPE::WORLD, world);

	// �萔�o�b�t�@�ɑ���
	m_vertexShader->BindShader();
	m_pixelShader->BindShader();

	ID3D11DeviceContext& deviceContext = SYSTEMS::DirectXGraphics::GetInstance()->GetImmediateContext();
	m_mesh->Draw(&deviceContext);
}

void GAME_SYSTEMS::SphereCollider::DebugRenderer::Finalize()
{
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_mesh->Uninit();
}
