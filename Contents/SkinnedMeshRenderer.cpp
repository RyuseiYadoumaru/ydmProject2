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

#include "../Assimpscene.h"
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

	// メッシュデータ生成
	AssimpScene assimpScene;
	assimpScene.Init(TEXT("Assets/ThirdPerson.fbx"));
	m_meshData = std::make_shared<Mesh>();
	m_meshData->Load(&assimpScene);

	m_skelton = std::make_shared<Skeleton>();
	m_skelton->Load(&assimpScene);

	m_animation = std::make_shared<Animation>();
	m_animation->SetSkeleton(m_skelton.get());

	assimpScene.Exit();

#ifndef ANIM_BLEND
	// アニメーション作成
	assimpScene.Init(TEXT("Assets/ThirdPersonIdle.FBX"));
	m_animClip = std::make_unique<AnimationClip>();
	m_animClip->Load(&assimpScene, 0);
	assimpScene.Exit();
	m_animation->AddAnimationClips(m_animClip.get());
#else
	// アニメーション追加
	Array<T_String, 3> animationNameList;
	animationNameList[0] = TEXT("Assets/ThirdPersonIdle.FBX");
	animationNameList[1] = TEXT("Assets/ThirdPersonWalk.FBX");
	animationNameList[2] = TEXT("Assets/ThirdPersonRun.FBX");


	// アニメーションクリップ生成
	for (int i = 0; i < animationNameList.size(); i++)
	{
		assimpScene.Init(animationNameList[i]);
		SharedPtr<AnimationClip> animPtr;
		animPtr = std::make_unique<AnimationClip>();
		animPtr->Load(&assimpScene, 0);
		m_animationClipList.emplace_back(std::move(animPtr));
		assimpScene.Exit();
	}

	// ブレンドアニメーション作成
	Float32 param = 0.0f;
	m_blendAnimation = std::make_shared<BlendAnimation>();
	for (auto& animClip : m_animationClipList)
	{
		m_blendAnimation->AddBlendSample(animClip.get(), param);
		param += 0.5f;
	}
	m_animation->AddAnimationClips(m_blendAnimation.get());

	// アニメーション追加
	for (auto& animClip : m_animationClipList)
	{
		m_animation->AddAnimationClips(animClip.get());
	}

#endif // !ANIM_BLEND

	// マテリアル生成
	// TODO : 現在はサンプルコードを直接生成することでマテリアルを作成している
	m_material = std::make_shared<Material>();
	m_material->LoadShader(TEXT("vsoneskin"), TEXT("graymanps"));

	// テクスチャ生成
	m_texture = std::make_shared<Texture>();
	m_texture->Load(TEXT("GraymanMaskTex.png"), "Assets");
}


void GAME_SYSTEMS::SkinnedMeshRenderer::Update()
{
	// アニメーションを更新する
	m_animation->SetBlendParameter(m_blendParam);
	m_animation->UpdateAnimation(1.0f / 60.0f);
	m_animation->UpdateConstantBufferBoneMatrix();

	// シェーダー生成
	m_material->SetShader();
	// テクスチャ生成
	m_texture->SetTexture(0);

	// ワールド行列をコンスタントバッファに生成する
	auto worldMatrix = m_ownerTransform->GetWorldMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, worldMatrix);
	DX11SetMaterial::GetInstance()->SetConstantBuffer(*m_material);

	// 描画
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
	m_meshData->Draw(&deviceContext);
}
void GAME_SYSTEMS::SkinnedMeshRenderer::End()
{
	m_meshData->Unload();
	m_material->Unload();
	m_ownerTransform = nullptr;
}
