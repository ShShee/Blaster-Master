#include "Item.h"

ItemHolder* ItemHolder::_instance = NULL;

void ItemHolder::LoadItemList()
{
	CTextures::GetInstance()->Add(ID_TEX_ITEM, L"SpritesSource\\weapon.png", D3DCOLOR_XRGB(54, 115, 1));
	texItem = CTextures::GetInstance()->Get(ID_TEX_ITEM);

	CSprites* sprites = CSprites::GetInstance();
	sprites->Add(50000,255,109,271,125,texItem);
	Item* addItem;
	addItem= new Item();
	addItem->Add_Image(50000);
	ItemList.push_back(addItem);
	sprites->Add(Bomber_Bullet, 258, 12, 268, 22,texItem);
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;
	ani = new CAnimation(300);
	ani->Add(Bomber_Bullet);
	animations->Add(Bomber_Bullet, ani);
}

int ItemHolder::GenerateItem(int Class)
{
	srand(time(NULL));
	if (Class == 0)
	{
		int res = rand()%100+1;
		if (res %2== 0)
		{
			return ItemList[PowerItem]->GetId();
		}
	}
	return -1;
}

int ItemHolder::AddItem(GameObject* gobj)
{
	DroppedItems.push_back(gobj);
	return DroppedItems.size() - 1;
}

GameObject* ItemHolder::GetDroppedItem(int id)
{
	if (id < 0) id=0;
	else return DroppedItems[id];
}

ItemHolder* ItemHolder::GetInstance()
{
	if (_instance == NULL) _instance = new ItemHolder();
	return _instance;
}
