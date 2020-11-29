#include "Item.h"

ItemHolder* ItemHolder::_instance = NULL;

void ItemHolder::LoadItemList()
{
	CTextures::GetInstance()->Add(ID_TEX_ITEM, L"SpritesSource\\weapon.png", D3DCOLOR_XRGB(54, 115, 1));
	texItem = CTextures::GetInstance()->Get(ID_TEX_ITEM);

	CSprites* sprites = CSprites::GetInstance();
	Item* addItem;
	sprites->Add(50000,255,109,271,125,texItem);
	addItem= new Item();
	addItem->Add_Image(50000);
	ItemList.push_back(addItem);

	sprites->Add(50001, 5, 59, 21, 75, texItem);
	addItem = new Item();
	addItem->Add_Image(50001);
	ItemList.push_back(addItem);

	sprites->Add(Bomber_Bullet, 258, 12, 268, 22,texItem);
	sprites->Add(Boss_Bullet, 58, 62, 67, 71, texItem);
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;
	ani = new CAnimation(300);
	ani->Add(Bomber_Bullet);
	animations->Add(Bomber_Bullet, ani);

	ani = new CAnimation(300);
	ani->Add(Boss_Bullet);
	animations->Add(Boss_Bullet, ani);

	sprites->Add(1255, 204, 158, 222, 176, texItem);
	sprites->Add(1256, 254, 158, 272, 176, texItem);
	sprites->Add(1257, 304, 158, 322, 176, texItem);
	sprites->Add(1258, 204, 158, 222, 176, texItem);

	ani = new CAnimation(100);
	for (int i = 1255; i < 1259; i++) ani->Add(i);
	animations->Add(754, ani);
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
	if (Class == 1) return ItemList[UpgradeItem]->GetId();
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
