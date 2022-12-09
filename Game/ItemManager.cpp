#include "ItemManager.h"
#include "Item.h"

USING_GAME_SYSTEMS;

void ItemManager::Start()
{
	// アイテム座標テーブル作成
	m_itemPositionTable.resize(10);
	m_itemPositionTable[0].Set(100.0f, 100.0f, 50.0f);
	m_itemPositionTable[1].Set(200.0f, 100.0f, 50.0f);
	m_itemPositionTable[2].Set(300.0f, 100.0f, 50.0f);
	m_itemPositionTable[3].Set(50.0f, 10.0f, 10.0f);
	m_itemPositionTable[4].Set(60.0f, 15.0f, 10.0f);
	m_itemPositionTable[5].Set(70.0f, 20.0f, 10.0f);
	m_itemPositionTable[6].Set(100.0f, 20.0f, 20.0f);
	m_itemPositionTable[7].Set(100.0f, 25.0f, 25.0f);
	m_itemPositionTable[8].Set(100.0f, 30.0f, 30.0f);
	m_itemPositionTable[9].Set(100.0f, 35.0f, 35.0f);

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
