#include "EndingScene.h"

EndingScene::EndingScene()
{
	wm = new WorldMap();
	quadtree = new Quadtree(1, new BoundingBox(0, 0, 2048, 2048));
	frog = new MovingObject(422.0f,1853.0f);
	SmallDetails = new MovingObject(120.0f,1848.0f,0,-0.01f);
	keyHandler = new NextKeyHandler();
}

void EndingScene::Update(DWORD dt)
{
	ListObject.clear();
	timer += vt * dt;
	CGame::GetInstance()->SetCamPos(location, lag);
	quadtree->GetListObjectinCamera(ListObject,
		new BoundingBox(CGame::GetInstance()->Get_CamX(), 2032 - CGame::GetInstance()->Get_CamY() > SCREEN_HEIGHT ? (2032 - CGame::GetInstance()->Get_CamY()) - SCREEN_HEIGHT : 0,
			SCREEN_WIDTH, SCREEN_HEIGHT));
	if (timer > 0 && timer < 1200)
	{
		Sound::getInstance()->play("collapse", true,0);
		SmallDetails->Update(dt);
		((timer > 0 && timer < 100) || (timer > 300 && timer < 400) 
		|| (timer > 600 && timer < 700) || (timer > 900 && timer < 1000)) ? lag = 1988.0f : lag = 1986.0f;
	}
	else if (timer >= 1200 && timer<1500)
	{
		Sound::getInstance()->stop("collapse");
		SmallDetails->SetAni(1);
		SmallDetails->SetPos(408, 1870);		
	}
	else if(timer>=2000 && timer<8000)
	{
		Sound::getInstance()->play("endingscene", true, 0);
		if(location<205)
		location += 0.05 * dt;
	}
	else if (timer >= 8000 && FlagTheEnd==false)
	{
		FlagTheEnd = true;
		frog->SetAni(1);
		frog->SetPos(location+20.0f, lag+20.0f);
		SmallDetails->SetAni(2);
		SmallDetails->SetPos(location+115.0f, 1740.0f);
		SmallDetails->SetSpeed(0, 0.03f);
		vt = 0;
	}
	else if (FlagTheEnd == true)
	{
		if(SmallDetails->Get_y()<1940)
		SmallDetails->Update(dt);
	}
}

void EndingScene::LoadContent()
{
	wm->LoadMap("SpritesSource\\Endingmap.tmx",3);
	wm->SetListItem();

	for (GameObject* gobj : wm->GetListMapItem())
	{
		quadtree->Insert(gobj);
	}
	frog->Add_Image(234);
	frog->Add_Image(235);
	SmallDetails->Add_Image(231);
	SmallDetails->Add_Image(232);
	SmallDetails->Add_Image(233);
}

void EndingScene::Render()
{
	if (timer < 8000)
	{
		vector<GameObject*>SaveForTheLast;
		for (GameObject* gobj : ListObject)
		{
			if (gobj->GetLayer() == MAIN_LAYER && timer < 1200)
				gobj->SetRenderColor(0);
			else gobj->SetRenderColor(255);
			if (gobj->GetLayer() == DOOR_LAYER)
				SaveForTheLast.push_back(gobj);
			else gobj->Render();
		}
		frog->Render();
		SmallDetails->Render();
		for (GameObject* gobj : SaveForTheLast)
		{
			gobj->Render();
		}
		SaveForTheLast.clear();
	}
	else
	{
		frog->Render();
		SmallDetails->Render();
	}
}

void NextKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
		case DIK_SPACE:
		SetState(CHANGE);
		break;
	}
}

