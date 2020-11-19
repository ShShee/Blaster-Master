#include "OverWorldScene.h"

OverWorldScene::OverWorldScene()
{
	ReadyPlayer1 = new MainPlayer();
	wm = new WorldMap();
	quadtree = new Quadtree(1, new BoundingBox(0, 0, 2048, 2048));
	keyHandler = new OverWorldKeyHandler();
}

void OverWorldScene::Update(DWORD dt)
{
	vector<GameObject*> coObjects;
	vector<GameObject*>Items;
	//vector<GameObject*> Items;
	CGame::GetInstance()->SetCamPos(ReadyPlayer1->Get_CurPlayer_lastX() - SCREEN_WIDTH / 2, ReadyPlayer1->Get_CurPlayer_lastY() + SCREEN_HEIGHT / 2/*0.0f,150.0f*/);

	////Items.clear();
	ListObject.clear();
	coObjects.clear();
	DoorLocation.clear();
	Items.clear();

	quadtree->GetListObjectinCamera(ListObject,
		new BoundingBox(CGame::GetInstance()->Get_CamX(), 2032 - CGame::GetInstance()->Get_CamY() > SCREEN_HEIGHT ? (2032 - CGame::GetInstance()->Get_CamY()) - SCREEN_HEIGHT : 0,
			SCREEN_WIDTH, SCREEN_HEIGHT));

	for (int i = 0; i < ListObject.size(); i++)
	{
		if (ListObject[i]->GetLayer() >= SCENE_DOOR && ListObject[i]->GetHP() > 0)
			coObjects.push_back(ListObject[i]);
		else if (ListObject[i]->GetLayer() == SPECIAL_DOOR1 || ListObject[i]->GetLayer() == SPECIAL_DOOR2)
			DoorLocation.push_back(ListObject[i]);
		if (ListObject[i]->GetHP() <= 0)
		{
			if (ListObject[i]->GetDropItemState() == HVNT_DROP_YET) ListObject[i]->DropItem();
			else if (ListObject[i]->GetDropItemState() == DROPPED)
			{
				GameObject* temp = ItemHolder::GetInstance()->GetDroppedItem(ListObject[i]->GetIdItemDroppped());
				if (temp->GetDropItemState() == HVNT_DROP_YET) Items.push_back(temp);
			}
		}
	}
	coObjects.push_back(ReadyPlayer1->Get_CurPlayerInfo());
	for (int i = 0; i < coObjects.size(); i++)
	{
		if (coObjects[i]->GetLayer() == ENEMIES_WITH_TARGET)
			coObjects[i]->Update(dt, &coObjects,
				ReadyPlayer1->Get_CurPlayer_lastX(), ReadyPlayer1->Get_CurPlayer_lastY());
	}
	coObjects.pop_back();
	for (GameObject* umobj : Items)
	{
		coObjects.push_back(umobj);
		ListObject.push_back(umobj);
	}
	ReadyPlayer1->SetItemSize(Items.size());
	if (keyHandler->GetFlageScene() == true)
	{
		ChangeSceneorNot() == true ? FlagChangeScene = true : FlagChangeScene = false;
		keyHandler->SetFlagScene(false);
	}
	ReadyPlayer1->SetAni(keyHandler->GetState());
	ReadyPlayer1->Update(dt, coObjects);
}

void OverWorldScene::LoadContent()
{
	CTextures* textures = CTextures::GetInstance();
	ReadyPlayer1->LoadTexture();
	wm->LoadMap("SpritesSource\\area2overmap.tmx",2);
	ItemHolder::GetInstance()->LoadItemList();

	ReadyPlayer1->SetPlayer(2);
	ReadyPlayer1->SetPos(110.0f, 140.0f/*100.0f, 66.0f*/);//66.0f);

	wm->SetListItem();

	for (GameObject* gobj : wm->GetListMapItem())
	{
		quadtree->Insert(gobj);
	}
}

#pragma region KeyEvent
void OverWorldKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_RIGHT))
		SetState(GO_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		SetState(GO_LEFT);
	else if (game->IsKeyDown(DIK_UP))
		SetState(GO_UP);
	else if (game->IsKeyDown(DIK_DOWN))
		SetState(GO_DOWN);
	else SetState(IDLE);
}

void OverWorldKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_Z:
		SetState(FIRE);
	case DIK_LCONTROL:
		SetFlagScene();
		break;
	}
}

void OverWorldKeyHandler::OnKeyUp(int KeyCode)
{
}
#pragma endregion