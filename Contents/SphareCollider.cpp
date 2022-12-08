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

bool GAME_SYSTEMS::SphereCollider::HitCheck(SharedPtr<SphereCollider> collider)
{
	//SphereCollider checkCol;
	//checkCol = collider;

	Float32 checkX = (collider->m_position.x - m_position.x);
	Float32 checkY = (collider->m_position.y - m_position.y);
	Float32 checkZ = (collider->m_position.z - m_position.z);
	
	Float32 check = 0.0f;
	check = std::powf(checkX, 2.0f) + std::powf(checkY, 2.0f) + std::powf(checkZ, 2.0f);

	Float32 checkRad = std::powf((collider->m_radius - m_radius), 2.0f);

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
	m_debug->Initialize();

#endif
}

void GAME_SYSTEMS::SphereCollider::Update()
{
	auto transform = GetOwner()->m_transform;
	m_position = transform->GetPosition();
	m_position += m_offset;

#ifdef _DEBUG
	if (m_isDebug == true)
	{
		m_debug->Render();
	}
#endif

}

void GAME_SYSTEMS::SphereCollider::End()
{
#ifdef _DEBUG
	m_debug->Finalize();
#endif
}


void GAME_SYSTEMS::SphereCollider::DebugRenderer::Initialize()
{
	m_vertexShader = ShaderManager::GetInstance()->GetVertexShader("DebugVertexShader");
	m_pixelShader = ShaderManager::GetInstance()->GetPixelShader("DebugPixelShader");

	// ���̂̃��b�V�������

}

void GAME_SYSTEMS::SphereCollider::DebugRenderer::Render()
{
	// ���[���h�s������

	// �萔�o�b�t�@�ɑ���
	m_vertexShader->BindShader();
	m_pixelShader->BindShader();

	ID3D11DeviceContext& deviceContext = SYSTEMS::DirectXGraphics::GetInstance()->GetImmediateContext();
	for (auto& mesh : m_meshList)
	{
		mesh->Draw(&deviceContext);
	}

}

void GAME_SYSTEMS::SphereCollider::DebugRenderer::Finalize()
{
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_meshList.clear();
}
