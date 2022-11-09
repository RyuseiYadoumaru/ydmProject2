#include "ActionTestScene.h"
#include "GameContents.h"

USING_GAME_SYSTEMS;
USING_MY_MATH;
USING_SYSTEMS;

#include "Material.h"

#include "../Assimpscene.h"
#include "../MeshData.h"
#include "../Texture.h"
#include "../Skeleton.h"
#include "../Animation.h"
#include "../AnimationClip.h"
#include "../BlendAnimation.h"

#include "../dx11mathutil.h"
#include "../System/DirectXGraphics.h"
#include "../DX11Settransform.h"

DirectX::XMFLOAT4X4 g_playerMtx;

MeshData g_meshData;
gameSystems::Material g_material;
Texture	 g_texture;
Skeleton g_skeleton;
Animation g_animation;
Vector<UniquePtr<AnimationClip>> g_animationClipList;
BlendAnimation g_blendAnimation;

Float32 g_animParam = 0.0f;


void ActionTestScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<DefaultCamera>("Camera");
}

void ActionTestScene::BeginPlay()
{
	SetDisplayColor(255.0f, 0.0f, 0.0f);

	// Assimpから読み込んだモデルのデータを保存する
	AssimpScene assimpScene;
	assimpScene.Init("Assets/ThirdPerson.fbx");

	// メッシュデータ読み込み
	g_meshData.Load(&assimpScene);
	// データからスケルトン読み込み
	g_skeleton.Load(&assimpScene);
	g_animation.SetSkeleton(&g_skeleton);

	// AssimpScene解放
	assimpScene.Exit();

	// アニメーション追加
	Array<T_String, 3> animationNameList;
	animationNameList[0] = TEXT("Assets/ThirdPersonIdle.FBX");
	animationNameList[1] = TEXT("Assets/ThirdPersonWalk.FBX");
	animationNameList[2] = TEXT("Assets/ThirdPersonRun.FBX");


	// アニメーションクリップ生成
	for (int i = 0; i < animationNameList.size(); i++)
	{
		assimpScene.Init(animationNameList[i]);
		UniquePtr<AnimationClip> animPtr;
		animPtr = std::make_unique<AnimationClip>();
		animPtr->Load(&assimpScene, 0);
		g_animationClipList.emplace_back(std::move(animPtr));
		assimpScene.Exit();
	}

	// ブレンドアニメーション作成
	Float32 param = 0.0f;
	for (auto& animClip : g_animationClipList)
	{
		g_blendAnimation.AddBlendSample(animClip.get(), param);
		param += 0.5f;
	}
	g_animation.AddAnimationClips(&g_blendAnimation);

	// アニメーション追加
	for (auto& animClip : g_animationClipList)
	{
		g_animation.AddAnimationClips(animClip.get());
	}

	// シェーダ読み込み
	g_material.LoadShader(TEXT("vsoneskin"), TEXT("graymanps"));

	// テクスチャ読み込み
	g_texture.Load("GraymanMaskTex.png", "Assets");

	DX11MtxIdentity(g_playerMtx);

	g_animParam = 0.0f;
}

void ActionTestScene::Tick()
{
	static Vector3 angle = { 90.0f,0.0f,0.0f }; // 角度情報
	static Vector3 trans = { 0.0f,0.0f,0.0f }; // 平行移動量

	// 移動量
	Vector3 moveForce = { 0.0f, 0.0f, 0.0f };
	// スピード
	Float32 speed = 5.0f;

	moveForce.x = speed * GamePad::LeftStick().x;
	moveForce.z = speed * GamePad::LeftStick().y;

	// ブレンドパラメータ更新
	g_animParam = Easing::SineOut(fabs(moveForce.z), speed, 0.0f, 1.0f);

	// 平行移動量追加
	trans += moveForce;
	g_playerMtx._41 = trans.x;
	g_playerMtx._42 = trans.y;
	g_playerMtx._43 = trans.z;
	DX11MakeWorldMatrix(g_playerMtx, angle, trans);

	// ブレンドパラメーターセット
	g_animation.SetBlendParameter(g_animParam);

	// アニメーションを更新する
	g_animation.UpdateAnimation(1.0f / 60.0f);
}

void ActionTestScene::EndPlay()
{
}

void ActionTestScene::Render()
{
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();

	// データをシェーダーに転送
	g_animation.UpdateConstantBufferBoneMatrix();
	g_material.SetShader();
	g_texture.SetTexture(0);

	// プレイヤー描画
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, g_playerMtx);
	g_meshData.Draw(&deviceContext);

}
