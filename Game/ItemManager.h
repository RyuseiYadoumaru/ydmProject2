#pragma once
#include "GameContents.h"

class Item;

class ItemManager : public GAME_SYSTEMS::Script
{
public:
	// アイテムリスト
	Vector<gameSystems::GameObjectPtr> GetItemList() noexcept { return m_itemList; }
	void DeleteItem(uInt32 index);

	// オブジェクト数
	uInt32 GetObjectCounter() const noexcept { return m_objectCounter; }
private:
	Vector<gameSystems::GameObjectPtr> m_itemList;
	uInt32 m_objectCounter = 0;
	Vector<MY_MATH::Vector3> m_itemPositionTable;

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

};
