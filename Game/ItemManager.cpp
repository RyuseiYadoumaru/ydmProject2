#include "ItemManager.h"
#include "Item.h"

USING_GAME_SYSTEMS;

void ItemManager::Start()
{
	// アイテム座標テーブル作成
	m_itemPositionTable.resize(10);
	m_itemPositionTable[0].Set(2500.0f, 300.0f, 300.0f);
	m_itemPositionTable[1].Set(3000.0f, 300.0f, 500.0f);
	m_itemPositionTable[2].Set(4000.0f, 300.0f, 800.0f);
	m_itemPositionTable[3].Set(1500.0f, 400.0f, 500.0f);
	m_itemPositionTable[4].Set(1600.0f, 450.0f, 900.0f);
	m_itemPositionTable[5].Set(1700.0f, 300.0f, 700.0f);
	m_itemPositionTable[6].Set(2600.0f, 300.0f, 2000.0f);
	m_itemPositionTable[7].Set(3200.0f, 250.0f, 2500.0f);
	m_itemPositionTable[8].Set(100.0f, 300.0f, 300.0f);
	m_itemPositionTable[9].Set(100.0f, 350.0f, 350.0f);

	// 取得アイテムを管理するため
	auto objectList = GameObjectManager::GetInstance()->GetGameObjectList();
	m_objectCounter = 0;
	for (auto& object : objectList)
	{
		if (object.second->GetTag() == Tag::Item)
		{
			m_itemList.emplace_back(object.second);
			m_itemList.back()->m_transform->m_Position = m_itemPositionTable[m_objectCounter];
			m_objectCounter++;
			TOOLS::Debug::Assert(m_objectCounter >= m_itemPositionTable.size());
		}
	}
}

void ItemManager::Update()
{
	if (m_itemList.empty() == false)
	{
		m_objectCounter = static_cast<uInt32>(m_itemList.size());
	}
}

void ItemManager::End()
{
	m_itemList.clear();
}
