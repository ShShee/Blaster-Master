#include "EndingScene.h"

EndingScene::EndingScene()
{
	wm = new WorldMap();
	quadtree = new Quadtree(1, new BoundingBox(0, 0, 2048, 2048));
	frog = new UnmovingObject(422.0f,1853.0f);
	SmallDetails = new Enemy(120.0f,1848.0f,0,-0.01f);
	keyHandler = new NextKeyHandler();
}

void EndingScene::Update(DWORD dt)
{
	ListObject.clear();
	timer<2000?timer += vt * dt:vt=0;
	vector<GameObject*> coOject;
	coOject.clear();
	CGame::GetInstance()->SetCamPos(location, lag);
	quadtree->GetListObjectinCamera(ListObject,
		new BoundingBox(CGame::GetInstance()->Get_CamX(), 2032 - CGame::GetInstance()->Get_CamY() > SCREEN_HEIGHT ? (2032 - CGame::GetInstance()->Get_CamY()) - SCREEN_HEIGHT : 0,
			SCREEN_WIDTH, SCREEN_HEIGHT));
	if (timer > 0 && timer < 1200)
	{
		Sound::getInstance()->play("collapse", true,0);
		SmallDetails->Update(dt, &coOject);
		((timer > 0 && timer < 100) || (timer > 300 && timer < 400) 
		|| (timer > 600 && timer < 700) || (timer > 900 && timer < 1000)) ? lag = 1988.0f : lag = 1986.0f;
	}
	else if (timer >= 1200 && timer<1500)
	{
		Sound::getInstance()->stop("collapse");
		SmallDetails->SetAni(1);
		SmallDetails->SetPos(408, 1870);		
	}
	else if(timer>=2000)
	{
		Sound::getInstance()->play("endingscene", true, 0);
		if(location<205)
		location += 0.05 * dt;
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
	frog->Add_Image(2119);
	SmallDetails->Add_Image(231);
	SmallDetails->Add_Image(232);
}

void EndingScene::Render()
{
	vector<GameObject*>SaveForTheLast;
	for (GameObject* gobj : ListObject)
	{
		if(gobj->GetLayer()==MAIN_LAYER && timer<1200)
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

void NextKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
		case DIK_SPACE:
		SetState(CHANGE);
		break;
	}
}

