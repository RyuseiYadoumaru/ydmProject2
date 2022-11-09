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

	// Assimp����ǂݍ��񂾃��f���̃f�[�^��ۑ�����
	AssimpScene assimpScene;
	assimpScene.Init("Assets/ThirdPerson.fbx");

	// ���b�V���f�[�^�ǂݍ���
	g_meshData.Load(&assimpScene);
	// �f�[�^����X�P���g���ǂݍ���
	g_skeleton.Load(&assimpScene);
	g_animation.SetSkeleton(&g_skeleton);

	// AssimpScene���
	assimpScene.Exit();

	// �A�j���[�V�����ǉ�
	Array<T_String, 3> animationNameList;
	animationNameList[0] = TEXT("Assets/ThirdPersonIdle.FBX");
	animationNameList[1] = TEXT("Assets/ThirdPersonWalk.FBX");
	animationNameList[2] = TEXT("Assets/ThirdPersonRun.FBX");


	// �A�j���[�V�����N���b�v����
	for (int i = 0; i < animationNameList.size(); i++)
	{
		assimpScene.Init(animationNameList[i]);
		UniquePtr<AnimationClip> animPtr;
		animPtr = std::make_unique<AnimationClip>();
		animPtr->Load(&assimpScene, 0);
		g_animationClipList.emplace_back(std::move(animPtr));
		assimpScene.Exit();
	}

	// �u�����h�A�j���[�V�����쐬
	Float32 param = 0.0f;
	for (auto& animClip : g_animationClipList)
	{
		g_blendAnimation.AddBlendSample(animClip.get(), param);
		param += 0.5f;
	}
	g_animation.AddAnimationClips(&g_blendAnimation);

	// �A�j���[�V�����ǉ�
	for (auto& animClip : g_animationClipList)
	{
		g_animation.AddAnimationClips(animClip.get());
	}

	// �V�F�[�_�ǂݍ���
	g_material.LoadShader(TEXT("vsoneskin"), TEXT("graymanps"));

	// �e�N�X�`���ǂݍ���
	g_texture.Load("GraymanMaskTex.png", "Assets");

	DX11MtxIdentity(g_playerMtx);

	g_animParam = 0.0f;
}

void ActionTestScene::Tick()
{
	static Vector3 angle = { 90.0f,0.0f,0.0f }; // �p�x���
	static Vector3 trans = { 0.0f,0.0f,0.0f }; // ���s�ړ���

	// �ړ���
	Vector3 moveForce = { 0.0f, 0.0f, 0.0f };
	// �X�s�[�h
	Float32 speed = 5.0f;

	moveForce.x = speed * GamePad::LeftStick().x;
	moveForce.z = speed * GamePad::LeftStick().y;

	// �u�����h�p�����[�^�X�V
	g_animParam = Easing::SineOut(fabs(moveForce.z), speed, 0.0f, 1.0f);

	// ���s�ړ��ʒǉ�
	trans += moveForce;
	g_playerMtx._41 = trans.x;
	g_playerMtx._42 = trans.y;
	g_playerMtx._43 = trans.z;
	DX11MakeWorldMatrix(g_playerMtx, angle, trans);

	// �u�����h�p�����[�^�[�Z�b�g
	g_animation.SetBlendParameter(g_animParam);

	// �A�j���[�V�������X�V����
	g_animation.UpdateAnimation(1.0f / 60.0f);
}

void ActionTestScene::EndPlay()
{
}

void ActionTestScene::Render()
{
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();

	// �f�[�^���V�F�[�_�[�ɓ]��
	g_animation.UpdateConstantBufferBoneMatrix();
	g_material.SetShader();
	g_texture.SetTexture(0);

	// �v���C���[�`��
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, g_playerMtx);
	g_meshData.Draw(&deviceContext);

}
