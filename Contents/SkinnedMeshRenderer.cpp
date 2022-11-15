//*****************************************************************************
//* @file   SkinnedMeshRenderer.cpp
//* @brief  
//* @note   ボーンアニメーションつきのメッシュを描画を行うコンポーネント
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "SkinnedMeshRenderer.h"

#include "../System/MessageWindow.h"
#include "../System/DX11Settransform.h"
#include "../System/DX11SetMaterial.h"
#include "../System/DX11SetBoneMatrix.h"
#include "Debug.h"
#include "GameObject.h"

USING_TOOLS;
USING_SYSTEMS;
USING_GAME_SYSTEMS

#define ANIM_BLEND

#include "Material.h"
#include "Mesh.h"
#include "Skeleton.h"

#include "../System/ThirdParty/Assimp/Assimpscene.h"
#include "../Texture.h"
#include "../Animation.h"
#include "../AnimationClip.h"
#include "../BlendAnimation.h"


void GAME_SYSTEMS::SkinnedMeshRenderer::Start()
{
	m_ownerTransform = GetOwner()->m_transform;
	if (m_ownerTransform == nullptr)
	{
		Debug::LogError("メッシュレンダラー : ", GetOwner()->ToString());
		MessageWindow::Error("トランスフォームがコンポーネントされていません!");
	}

	// メッシュデータ作成
	m_mesh = std::make_shared<SkeletalMesh>();
	m_mesh->Load(TEXT("Assets/ThirdPerson.fbx"));
	m_mesh->SetAnimationClip(TEXT("Assets/ThirdPersonIdle.FBX"));

	// マテリアル生成
	// TODO : 現在はサンプルコードを直接生成することでマテリアルを作成している
	m_material = std::make_shared<Material>();
	m_material->LoadShader(TEXT("SkinnedVertexShader"), TEXT("GrayManps"));

	// テクスチャ生成
	m_texture = std::make_shared<Texture>();
	m_texture->Load(TEXT("GraymanMaskTex.png"), "Assets");

}

void GAME_SYSTEMS::SkinnedMeshRenderer::Update()
{
	// シェーダー生成
	m_material->SetShader();
	// テクスチャ生成
	m_texture->SetTexture(0);

	// ワールド行列をコンスタントバッファに生成する
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// 描画
	m_mesh->Render();
}
void GAME_SYSTEMS::SkinnedMeshRenderer::End()
{
	m_mesh->Releace();
	m_material->Unload();
	m_ownerTransform = nullptr;
}
