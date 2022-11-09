//*****************************************************************************
//* @file   MeshRenderer.cpp
//* @brief  
//* @note   メッシュの描画を行うためのコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************

#include "../System/MessageWindow.h"
#include "../DX11Settransform.h"
#include "Debug.h"
#include "MeshRenderer.h"
#include "GameObject.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#include "Material.h"

#include "../Assimpscene.h"
#include "../MeshData.h"
#include "../Texture.h"
#include "../Skeleton.h"
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
	AssimpScene assimpScene;
	assimpScene.Init(TEXT("Assets/ThirdPerson.fbx"));
	m_meshData = std::make_shared<MeshData>();
	m_meshData->Load(&assimpScene);

	m_skelton = std::make_shared<Skeleton>();
	m_skelton->Load(&assimpScene);

	m_animation = std::make_shared<Animation>();
	m_animation->SetSkeleton(m_skelton.get());

	assimpScene.Exit();

	// アニメーション作成
	assimpScene.Init(TEXT("Assets/ThirdPersonIdle.FBX"));
	m_animClip = std::make_unique<AnimationClip>();
	m_animClip->Load(&assimpScene, 0);
	assimpScene.Exit();
	m_animation->AddAnimationClips(m_animClip.get());

	// マテリアル生成
	// TODO : 現在はサンプルコードを直接生成することでマテリアルを作成している
	m_material = std::make_shared<Material>();
	m_material->LoadShader(TEXT("vsoneskin"), TEXT("graymanps"));

	// テクスチャ生成
	m_texture = std::make_shared<Texture>();
	m_texture->Load(TEXT("GraymanMaskTex.png"), "Assets");

	DX11MtxIdentity(m_mtx);
}

void GAME_SYSTEMS::MeshRenderer::Update()
{
	// アニメーションを更新する
	m_animation->SetBlendParameter(1.0f);

	m_animation->UpdateAnimation(1.0f / 60.0f);
	m_animation->UpdateConstantBufferBoneMatrix();

	// シェーダー生成
	m_material->SetShader();
	// テクスチャ生成
	m_texture->SetTexture(0);

	// ワールド行列をコンスタントバッファに生成する
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);

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
