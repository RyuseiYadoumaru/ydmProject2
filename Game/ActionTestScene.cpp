#include "ActionTestScene.h"
#include "SceneManager.h"
#include "Mouse.h"
#include "macro.h"

USING_GAME_SYSTEMS;
USING_SYSTEMS;

#include "../Assimpscene.h"
#include "../MeshData.h"
#include "../Material.h"
#include "../Texture.h"
#include "../Skeleton.h"
#include "../Animation.h"
#include "../AnimationClip.h"

#include "../DX11Settransform.h"
#include "../CCamera.h"
#include "../dx11mathutil.h"
#include "../System/DirectXGraphics.h"

DirectX::XMFLOAT4X4 g_playerMtx;

MeshData g_meshData;
Material g_material;
Texture	 g_texture;
Skeleton g_skeleton;
Animation g_animation;
UniquePtr<AnimationClip> g_animationClip;



void ActionTestScene::ObjectEntry()
{
}

void ActionTestScene::BeginPlay()
{

#pragma region 

	// �J�����Z�b�g�A�b�v
	// �J����
	XMFLOAT3 eye = { 0.0f,100.0f,-300.0f };
	XMFLOAT3 lookat = { 0.0f,100.0f,0.0f };
	XMFLOAT3 up = { 0.0f,1.0f,0.0f };
	float screenX = 1280.0f;
	float screenY = 920.0f;
	CCamera::GetInstance()->Init(1.0f, 10000.0f, XM_PI / 2.0f, screenX, screenY, eye, lookat, up);
	// �萔�o�b�t�@������
	DX11SetTransform::GetInstance()->Init();
	// ���p�̒萔�o�b�t�@������
	Skeleton::InitConstantBufferBoneMatrix(&DirectXGraphics::GetInstance()->GetDevice());

#pragma endregion ���t�@�N�^

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
	T_String animationName;
	animationName = "Assets/ThirdPersonIdle.FBX";

	// �A�j���[�V�����N���b�v����
	assimpScene.Init(animationName);
	UniquePtr<AnimationClip> animPtr;
	animPtr = std::make_unique<AnimationClip>();
	animPtr->Load(&assimpScene, 0);
	g_animationClip = std::move(animPtr);
	assimpScene.Exit();

	// �A�j���[�V�����N���b�v�ǉ�
	g_animation.AddAnimationClips(g_animationClip.get());

	// �V�F�[�_�ǂݍ���
	g_material.LoadShader(TEXT("Shader/vsoneskin.fx"), TEXT("Shader/graymanps.fx"));

	// �e�N�X�`���ǂݍ���
	g_texture.Load("GraymanMaskTex.png", "Assets");

	DX11MtxIdentity(g_playerMtx);

}

void ActionTestScene::Tick()
{
	static XMFLOAT3 angle = { 90.0f,0.0f,0.0f }; // �p�x���

	static XMFLOAT3 trans = { 0.0f,0.0f,0.0f }; // ���s�ړ���


	DX11MakeWorldMatrix(g_playerMtx, angle, trans);

	if (Mouse::Click(MouseCode::Left) == true)
	{
		SceneManager::GetInstance()->LoadScene("TestScene");
	}

	g_animation.UpdateAnimation(1.0f / 60.0f);
}

void ActionTestScene::EndPlay()
{
}

void ActionTestScene::Render()
{
	ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();

	// �J�����s��Z�b�g
	auto cameraMtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, cameraMtx);

	auto projectionMtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, projectionMtx);

	// �f�[�^���V�F�[�_�[�ɓ]��
	g_animation.UpdateConstantBufferBoneMatrix();
	g_material.SetShader();
	g_texture.SetTexture(0);

	// �v���C���[�`��
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, g_playerMtx);
	g_meshData.Draw(&deviceContext);

}
