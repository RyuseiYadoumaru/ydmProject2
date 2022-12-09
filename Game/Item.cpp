#include "Item.h"

USING_GAME_SYSTEMS;

void Item::Setting()
{
	// �����_�[�ݒ�
	auto meshRender = AddComponent<MeshRenderer>();
	auto model = ResourceManager::GetInstance()->GetModelData("Cube.fbx");
	meshRender->SetMesh(model->GetModel(0));
	meshRender->GetMaterial()->AddTexture(ResourceManager::GetInstance()->GetTexture("gold.jpg"), 0);

	m_transform->m_Scale.Set(0.5f, 0.5f, 0.5f);

	// �R���C�_
	auto collider = AddComponent<SphereCollider>();
	collider->SetRadius(10.0f);
	collider->SetIsDebug(true);

	m_tag = Tag::Item;
}