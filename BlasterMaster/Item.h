#pragma once
#include "GameObject.h"
#include <time.h>

#define PowerItem 0
#define UpgradeItem 1
#define FullHpItem 2
#define PowerSprite 50000
#define UpgradeSprite 50001
#define FullHpSprite 50002
#define Bomber_Bullet 49999
#define Boss_Bullet 49998
class Item : public MovingObject
{
protected:
	int idSprite;
public:
	Item() :MovingObject() { this->layer = ITEM_LAYER; }
	void Add_Image(int ID) { MovingObject::Add_Image(ID); this->idSprite = ID; }
	int GetId() { return this->idSprite; }
	//void Render() { if (DropItemState != PICKED) UnmovingObject::Render(); }
};
class ItemHolder
{
	static ItemHolder* _instance;
	LPDIRECT3DTEXTURE9 texItem;
	vector<Item*> ItemList;
	vector<GameObject*> DroppedItems;
public:
	void LoadItemList();
	int GenerateItem(int Class);
	int AddItem(GameObject* gobj);
	int GetItemId(int location) { return ItemList[location]->GetId(); }
	Item* GetItem(int id) { return ItemList[id]; }
	GameObject* GetDroppedItem(int id);
	static ItemHolder* GetInstance();
};

