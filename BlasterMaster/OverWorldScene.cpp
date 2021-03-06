#include "OverWorldScene.h"

OverWorldScene::OverWorldScene()
{
	ReadyPlayer1 = new MainPlayer();
	wm = new WorldMap();
	quadtree = new Quadtree(1, new BoundingBox(0, 0, 2048, 2048));
	keyHandler = new OverWorldKeyHandler();
	FinalBoss = new Boss();
}

void OverWorldScene::Update(DWORD dt)
{
	switch (Gate)
	{
	case 1:
		ReadyPlayer1->SetPos(107.0f, 137.0f);
		break;
	case 2:
		ReadyPlayer1->SetPos(1436.0f, 870.0f);
		break;
	default:
		break;
	}
	Gate = 0;
	timerBF += vtBF * dt;
	vector<GameObject*> coObjects;
	vector<GameObject*>Items;
	//vector<GameObject*> Items;
	CGame::GetInstance()->SetCamPos(ReadyPlayer1->Get_CurPlayer_lastX() - SCREEN_WIDTH / 2, ReadyPlayer1->Get_CurPlayer_lastY() + SCREEN_HEIGHT / 2/*0.0f,150.0f*/);

	////Items.clear();
	ListObject.clear();
	coObjects.clear();
	DoorLocation.clear();
	Items.clear();
	(ReadyPlayer1->GetBossFight() == true && timerBF<=500) ? vtBF = 0.5f : vtBF = 0.0f;
	if (ReadyPlayer1->GetBossFight()== false || timerBF<500)
	{
		quadtree->GetListObjectinCamera(ListObject,
			new BoundingBox(CGame::GetInstance()->Get_CamX(), 2032 - CGame::GetInstance()->Get_CamY() > SCREEN_HEIGHT ? (2032 - CGame::GetInstance()->Get_CamY()) - SCREEN_HEIGHT : 0,
				SCREEN_WIDTH, SCREEN_HEIGHT));

		for (int i = 0; i < ListObject.size(); i++)
		{
			if ((ListObject[i]->GetLayer() >= SCENE_DOOR||ListObject[i]->GetLayer()==ITEM_LAYER) && ListObject[i]->GetHP() > 0)
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
			else if (coObjects[i]->GetLayer() == ENEMIES_WITHOUT_TARGET)
				coObjects[i]->Update(dt, &coObjects);
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
	}
	else
	{
		Sound::getInstance()->stop("stage1");
		Sound::getInstance()->play("bossfight", true, 0);
		if (FinalBoss->GetHP() > 0)
		{
			coObjects.push_back(ReadyPlayer1->Get_CurPlayerInfo());
			FinalBoss->Update(dt, &coObjects);
			if (FinalBoss->IsAttackable() == true)
			{
				coObjects.pop_back();
				coObjects.push_back(FinalBoss);
			}
		}
		else
		{
			HasBoss = true;
			FlagChangeScene = true;
		}		
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
	//ReadyPlayer1->SetPos(860.0f, 1200.0f/*100.0f, 66.0f*/);//66.0f);

	wm->SetListItem();

	for (GameObject* gobj : wm->GetListMapItem())
	{
		quadtree->Insert(gobj);
	}

	FinalBoss->LoadContent();
}

void OverWorldScene::Render()
{
	if (timerBF >= 500)
	{
		FinalBoss->Render();
	}
	if (ReadyPlayer1->GetBossFight() == false 
		|| timerBF<50 ||(timerBF>100 && timerBF<150)|| (timerBF > 200 && timerBF < 250)
		|| (timerBF > 300 && timerBF < 350) || (timerBF>400 && timerBF<450))
	{
		MainAreaScene::Render();
	}
	else
	{
		ReadyPlayer1->Render();
		CGame::GetInstance()->DrawHealthbars(CTextures::GetInstance()->Get(ID_TEX_HEALTHBAR), ReadyPlayer1->Get_CurPlayerHP());
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
		Sound::getInstance()->play("fire", false, 1);
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