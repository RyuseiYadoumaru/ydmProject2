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
#include "TextureManager.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#include "StaticMesh.h"
#include "Material.h"
#include "Texture.h"
#include "../System/ThirdParty/Assimp/Assimpscene.h"


void GAME_SYSTEMS::MeshRenderer::Start()
{
	// トランスフォーム取得
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("メッシュレンダラー : ", GetOwner()->ToString());
		MessageWindow::Error("トランスフォームがコンポーネントされていません!");
	}

	// マテリアル生成
	m_material = m_meshData->GetMaterial();
	m_material->AddTexture(TextureManager::GetInstance()->GetTexture(TEXT("MeshTexture.png")), 0);
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	// 定数バッファ設定
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// シェーダー生成
	m_material->SetShader();

	// 描画
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	m_meshData->Render();
}

void GAME_SYSTEMS::MeshRenderer::End()
{
	m_material->Unload();
	m_material = nullptr;
	m_ownerTransform = nullptr;
}
