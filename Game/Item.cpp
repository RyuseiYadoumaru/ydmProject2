#include "Item.h"

USING_GAME_SYSTEMS;

void Item::Setting()
{
	// レンダー設定
	auto meshRender = AddComponent<MeshRenderer>();
	auto model = ResourceManager::GetInstance()->GetGeometry(ResourceManager::GeometryType::Sphare);
	//auto model = ResourceManager::GetInstance()->GetModelData("Cube.fbx");
	meshRender->SetMesh(model);
	//meshRender->SetMesh(model->GetModel(0));

	//m_transform->m_Scale.Set(30.0f, 30.0f, 30.0f);

	// コライダ
	auto collider = AddComponent<SphereCollider>();
	collider->SetRadius(50.0f);
	collider->SetIsDebug(true);

	m_tag = Tag::Item;
}