#include "MainAreaScene.h"

#pragma region Processing Function
//Change from Sophia to Jason and backward
void MainAreaScene::SwitchPlayer()
{
	if (ReadyPlayer1->Get_CurPlayer() == 0 && ReadyPlayer1->GetFallingState() == false)
	{
		ReadyPlayer1->SetAni(GET_OUT);
		ReadyPlayer1->SetPlayer(1);
		ReadyPlayer1->SetPos(ReadyPlayer1->Get_Player_X(0) + 8.0f, ReadyPlayer1->Get_Player_Y(0));
		ReadyPlayer1->SetAni(JUMP);
	}
	else if (ReadyPlayer1->Get_CurPlayer() == 1 &&
		ReadyPlayer1->GetBB(0)->IsContain(ReadyPlayer1->GetBB(1)) == true)
	{
		ReadyPlayer1->SetPos(ReadyPlayer1->Get_Player_X(0) + 8.0f, ReadyPlayer1->Get_Player_Y(0));
		ReadyPlayer1->SetAni(JUMP);
		ReadyPlayer1->SetPlayer(0);
		ReadyPlayer1->SetAni(GET_IN);
	}
}

//Check flag change to init next scene
bool MainAreaScene::ChangeSceneorNot()
{
	int curPlayer = ReadyPlayer1->Get_CurPlayer();
	if (curPlayer != 0)
	{
		for (UINT i = 0; i < DoorLocation.size(); i++)
		{
			if (DoorLocation[i]->GetBoundingBox()->IsContain(ReadyPlayer1->GetBB(curPlayer)))
			{
				Gate = DoorLocation[i]->GetLayer() - 3;
				return true;
			}
		}
	}
	return false;
}
#pragma endregion

MainAreaScene::MainAreaScene()
{
	ReadyPlayer1 = new MainPlayer();
	wm = new WorldMap();
	quadtree = new Quadtree(1, new BoundingBox(0, 0, 2048, 2048));
	keyHandler = new MainAreaKeyHandler();
}

void MainAreaScene::Update(DWORD dt)
{
	vector<GameObject*> coObjects;
	vector<GameObject*> Items;
	CGame::GetInstance()->SetCamPos(ReadyPlayer1->Get_CurPlayer_lastX() - SCREEN_WIDTH / 2, ReadyPlayer1->Get_CurPlayer_lastY() + SCREEN_HEIGHT / 2/*0.0f,150.0f*/);

	Items.clear();
	ListObject.clear();
	coObjects.clear();
	DoorLocation.clear();

	//Get objects on cam
	quadtree->GetListObjectinCamera(ListObject,
		new BoundingBox(CGame::GetInstance()->Get_CamX(), 2032 - CGame::GetInstance()->Get_CamY() > SCREEN_HEIGHT ? (2032 - CGame::GetInstance()->Get_CamY()) - SCREEN_HEIGHT : 0,
			SCREEN_WIDTH+50.0f, SCREEN_HEIGHT+50.0f));

	//Classify objects and items
	for (int i = 0; i < ListObject.size(); i++)
	{
		if ((ListObject[i]->GetLayer() >= SCENE_DOOR) && ListObject[i]->GetHP() > 0)
			coObjects.push_back(ListObject[i]);
		else if (ListObject[i]->GetLayer() == SPECIAL_DOOR1 || ListObject[i]->GetLayer() == SPECIAL_DOOR2)
			DoorLocation.push_back(ListObject[i]);
		if (ListObject[i]->GetHP() <= 0)//Drop items
		{
			if (ListObject[i]->GetDropItemState() == HVNT_DROP_YET) ListObject[i]->DropItem();
			else if (ListObject[i]->GetDropItemState() == DROPPED)
			{
				GameObject* temp = ItemHolder::GetInstance()->GetDroppedItem(ListObject[i]->GetIdItemDroppped());
				if (temp->GetDropItemState() == HVNT_DROP_YET) Items.push_back(temp); //HVNT_DROP_YET because items will be created with this state first
			}
		}
	}

	//Add main player from collision list to update enemies
	coObjects.push_back(ReadyPlayer1->Get_CurPlayerInfo());
	for (int i = 0; i < coObjects.size(); i++)
	{
		if (coObjects[i]->GetLayer() == ENEMIES_WITH_TARGET)
			coObjects[i]->Update(dt, &coObjects,
				ReadyPlayer1->Get_CurPlayer_lastX(), ReadyPlayer1->Get_CurPlayer_lastY());
		else if (coObjects[i]->GetLayer() == ENEMIES_WITHOUT_TARGET)
			coObjects[i]->Update(dt, &coObjects);
	}
	coObjects.pop_back();

	//Add items for colliding 
	for (GameObject* umobj : Items)
	{
		coObjects.push_back(umobj);
		ListObject.push_back(umobj);
	}
	ReadyPlayer1->SetItemSize(Items.size());
	 
	//Process key + weapon + pos + change main + change scene
	ReadyPlayer1->SetReleaseKey(keyHandler->GetReleasedState());
	ReadyPlayer1->SetSpecialWeapon(keyHandler->GetSpecialWeapon());
	if (keyHandler->GetFlagPos() == true)
	{
		D3DXVECTOR2 newpos = keyHandler->GetPos();
		ReadyPlayer1->SetPos(newpos.x, newpos.y);
	}
	if (keyHandler->GetSwitch() == true)
	{
		SwitchPlayer();
	}
	if (keyHandler->GetFlageScene() == true)
	{
		ChangeSceneorNot() == true ? FlagChangeScene = true : FlagChangeScene = false;
		keyHandler->SetFlagScene(false);
	}
	ReadyPlayer1->SetAni(keyHandler->GetState());
	ReadyPlayer1->Update(dt, coObjects);
	//ReadyPlayer1->Update(dt, Items);
	//for (GameObject* gobj : ListObject)
	//{
	//	if (gobj->IsAbletoMove() == true)
	//		gobj->Update(dt, ReadyPlayer1->Get_CurPlayer_X(), ReadyPlayer1->Get_CurPlayer_Y());
	//}
}

void MainAreaScene::LoadContent()
{
	ItemHolder::GetInstance()->LoadItemList();
	ReadyPlayer1->LoadTexture();
	wm->LoadMap("SpritesSource\\area2map.tmx");

	ReadyPlayer1->SetPlayer(0);
	ReadyPlayer1->SetPos(1050.0f, 870.0f/*100.0f, 66.0f*/);//66.0f);

	wm->SetListItem();

	for (GameObject* gobj : wm->GetListMapItem())
	{
		quadtree->Insert(gobj);
	}
}

void MainAreaScene::Render()
{
	vector<GameObject*>SaveForTheLast;
	for (GameObject* gobj : ListObject)
	{
					if (gobj->IsAbletoMove() == true || gobj->GetLayer()==DOOR_LAYER || gobj->GetLayer()==ITEM_LAYER)
						SaveForTheLast.push_back(gobj);
					else if(gobj->GetLayer()<DOOR_LAYER) gobj->Render();
	}
	ReadyPlayer1->Render();
	for (GameObject* gobj : SaveForTheLast)
	{
		gobj->Render();
	}
	CGame::GetInstance()->DrawHealthbars(CTextures::GetInstance()->Get(ID_TEX_HEALTHBAR), ReadyPlayer1->Get_CurPlayerHP());
	SaveForTheLast.clear();
}

bool MainAreaScene::HasBeenDeadYet()
{
	bool temp = ReadyPlayer1->GetFlagDead();
	ReadyPlayer1->SetFlagDead(false);
    return temp;
}

#pragma region KeyEvent
void MainAreaKeyHandler::KeyState(BYTE* states)
{
	CGame* game=CGame::GetInstance();
	if (game->IsKeyDown(DIK_RIGHT))
		SetState(GO_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		SetState(GO_LEFT);
	else if (game->IsKeyDown(DIK_UP))
	{
		if (GetState() ==GO_LEFT || GetState() == GO_RIGHT) SetState(IDLE);
		else SetState(GO_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
		SetState(GO_DOWN);
	else SetState(IDLE);
}

void MainAreaKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	//case DIK_UP:
	//	SetState(GO_UP);
	//	break;
	case DIK_X:
		Sound::getInstance()->play("jump", false, 1);
		SetState(JUMP);		
		break;
	case DIK_Z:
		Sound::getInstance()->play("fire", false, 1);
		SetState(FIRE);
		break;
	case DIK_A:
		SetSpecialWeapon(1);
		break;
	case DIK_1:
		SetFlagPos();
		SetPos(D3DXVECTOR2(/*1050.0f+*/940.0f, 638.0f));
		break;
	case DIK_3:
		SetFlagPos();
		SetPos(D3DXVECTOR2(1200.0f, 1400.0f));
		break;
	case DIK_2:
		SetFlagPos();
		SetPos(D3DXVECTOR2(570.0f, 1570.0f));
		break;
	case DIK_LSHIFT:
		SetSwitch();
		break;
	case DIK_LCONTROL:
		SetFlagScene();
		break;
	}
}

void MainAreaKeyHandler::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
		SetReleasedState(GO_UP);
		break;
	}
}
#pragma endregion