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

#include "Material.h"
#include "Mesh.h"
#include "Skeleton.h"

#include "../Assimpscene.h"
#include "../Texture.h"
#include "../Animation.h"
#include "../AnimationClip.h"
#include "../BlendAnimation.h"

void GAME_SYSTEMS::MeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("メッシュレンダラー : ", GetOwner()->ToString());
		MessageWindow::Error("トランスフォームがコンポーネントされていません!");
	}

	// メッシュデータ生成
	m_meshData = std::make_shared<Mesh>();
	m_meshData->LoadCube();

	// マテリアル生成
	m_material = std::make_shared<Material>();
	if (m_useLit == true)
	{
		m_material->LoadShader(TEXT("vs"), TEXT("ps"));
	}
	else
	{
		m_material->LoadShader(TEXT("ShapeVertexShader"), TEXT("ShapePixelShader"));
	}
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	// アニメーションを更新する
	//m_animation->SetBlendParameter(1.0f);

	//m_animation->UpdateAnimation(1.0f / 60.0f);
	//m_animation->UpdateConstantBufferBoneMatrix();

	// 定数バッファ設定
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// シェーダー生成
	m_material->SetShader();
	// テクスチャ生成
	//m_texture->SetTexture(0);

	// 描画
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	m_meshData->Draw(&deviceContext);
}

void GAME_SYSTEMS::MeshRenderer::End()
{
	m_meshData->Unload();
	m_material->Unload();
	m_ownerTransform = nullptr;
}
