#pragma once
#include "GameObject.h"
#include <time.h>

#define PowerItem 0
#define Bomber_Bullet 49999
class Item : public UnmovingObject
{
protected:
	int idSprite;
public:
	Item() :UnmovingObject() { this->layer = ITEM_LAYER; }
	void Add_Image(int ID) { UnmovingObject::Add_Image(ID); this->idSprite = ID; }
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

