#include "TestScene.h"\
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "TestObject.h"
#include "CubeTest.h"
#include "DefaultCamera.h"
#include "MainCamera.h"
#include "SphareTest.h"
#include "GameContents.h"

#include "EnemyGenerator.h"
#include "PlayerMovement.h"
#include "ThirdPersonCamera.h"

USING_GAME_SYSTEMS;

void TestScene::ObjectEntry()
{
	GameObjectManager::GetInstance()->Instance<MainCamera>("Camera");
	m_test = GameObjectManager::GetInstance()->Instance<TestObject>("Player");
	m_obj = GameObjectManager::GetInstance()->Instance<CubeTest>("Cube");
	
	//m_ene = GameObjectManager::GetInstance()->Instance("EnemyGenerator");
	//m_ene->AddComponent<EnemyGenerator>();
	//auto render = m_ene->AddComponent<MeshRenderer>();
	//render->SetMesh(ResourceManager::GetInstance()->GetStaticMesh("Spider.obj"));
	//render->GetMaterial()->AddTexture(TextureManager::GetInstance()->GetTexture("SpiderNormal.jpg"), 0);
	//render->GetMaterial()->SetPixelShader("GrayManps");
}

void TestScene::BeginPlay()
{
	SetDisplayColor(0.0f, 1.0f, 0.0f);
	//m_test->m_transform->m_rotation.y = 90.0f;
	//m_obj->m_transform->m_scale.Set(100.0f, 100.0f, 100.0f);
	m_obj->m_transform->m_rotation.Set(0.0f, 90.0f, 0.0f);

	//m_ene->m_transform->m_position.Set(2000.0f, 50.0f, -2000.0f);
	//m_ene->m_transform->m_rotation.Set(0.0f, 0.0f, 0.0f);
	//m_ene->m_transform->m_scale.Set(3.0f, 3.0f, 3.0f);

}

void TestScene::Tick()
{
	//if (Keyboard::Trigger(Keycode::A) ||
	//	GamePad::Trigger(Xinput::A))
	//{
	//	SceneManager::GetInstance()->LoadScene("ActionTestScene");
	//}

}

void TestScene::EndPlay()
{
}

