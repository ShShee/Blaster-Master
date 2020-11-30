#include "Item.h"

ItemHolder* ItemHolder::_instance = NULL;

void ItemHolder::LoadItemList()
{
	CTextures::GetInstance()->Add(ID_TEX_ITEM, L"SpritesSource\\weapon.png", D3DCOLOR_XRGB(54, 115, 1));
	texItem = CTextures::GetInstance()->Get(ID_TEX_ITEM);

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;
	Item* addItem;
	sprites->Add(PowerSprite,255,109,271,125,texItem);
	addItem= new Item();
	ani = new CAnimation(100);
	ani->Add(PowerSprite);
	animations->Add(PowerSprite, ani);
	addItem->Add_Image(PowerSprite);
	ItemList.push_back(addItem);

	sprites->Add(UpgradeSprite, 5, 59, 21, 75, texItem);
	addItem = new Item();
	ani = new CAnimation(100);
	ani->Add(UpgradeSprite);
	animations->Add(UpgradeSprite, ani);
	addItem->Add_Image(UpgradeSprite);
	ItemList.push_back(addItem);

	sprites->Add(FullHpSprite, 255, 133, 271, 149, texItem);
	addItem = new Item();
	ani = new CAnimation(200);
	ani->Add(PowerSprite);
	ani->Add(FullHpSprite);
	animations->Add(FullHpSprite, ani);
	addItem->Add_Image(FullHpSprite);
	ItemList.push_back(addItem);

	sprites->Add(Bomber_Bullet, 258, 12, 268, 22,texItem);
	sprites->Add(Boss_Bullet, 58, 62, 67, 71, texItem);

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
	if (Class == UpgradeItem || Class==FullHpItem) return ItemList[Class]->GetId();
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
