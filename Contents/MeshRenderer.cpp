//*****************************************************************************
//* @file   MeshRenderer.cpp
//* @brief  
//* @note   メッシュの描画を行うためのコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "MeshRenderer.h"

#include "../System/MessageWindow.h"
#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "Debug.h"
#include "GameObject.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#include "StaticMesh.h"
#include "Material.h"
#include "../System/ThirdParty/Assimp/Assimpscene.h"
#include "../Texture.h"


void GAME_SYSTEMS::MeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("メッシュレンダラー : ", GetOwner()->ToString());
		MessageWindow::Error("トランスフォームがコンポーネントされていません!");
	}

	// マテリアル生成
	m_material = m_meshData->GetMaterial();

	// テクスチャ生成
	m_texture = std::make_shared<Texture>();
	m_texture->Load(TEXT("MeshTexture.png"), TEXT("Assets"));
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	// 定数バッファ設定
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// シェーダー生成
	m_material->SetShader();
	// テクスチャ生成
	m_texture->SetTexture(0);

	// 描画
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	m_meshData->Render();
}

void GAME_SYSTEMS::MeshRenderer::End()
{
	//m_meshData->Releace();
	//m_meshData->Unload();
	//m_material->Unload();
	m_ownerTransform = nullptr;
}
