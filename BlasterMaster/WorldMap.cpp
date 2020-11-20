#include "WorldMap.h"

void WorldMap::LoadMap(const char* filePath,int type)
{
	this->type = type;

	WMap = new Tmx::Map();
	WMap->ParseFile(filePath);
	
	const Tmx::Tileset* tileset = WMap->GetTileset(0);

	if(type==1)
	CTextures::GetInstance()->Add(ID_TEX_TILESET, L"SpritesSource\\level2-side_bank.png", D3DCOLOR_XRGB(0, 255, 255));
	else
	CTextures::GetInstance()->Add(ID_TEX_TILESET, L"SpritesSource\\level2-over_bank.png", D3DCOLOR_XRGB(0, 255, 255));
	CTextures::GetInstance()->Add(ID_TEX_ENEMY, L"SpritesSource\\Enemies.png", D3DCOLOR_XRGB(255, 255, 255));
	CTextures::GetInstance()->Add(ID_TEX_TEST, L"SpritesSource\\Untitled.png", D3DCOLOR_XRGB(255, 255, 255));

	texMap = CTextures::GetInstance()->Get(ID_TEX_TILESET);
	texEnemy = CTextures::GetInstance()->Get(ID_TEX_ENEMY);
}
void WorldMap::SetEnemiesTexture()
{

}
void WorldMap::SetListItem()
{
	int id,left,top,right,bottom,idEnemy;
	this->type == 1 ? id = 3000, idEnemy = 1000 : id = 60000, idEnemy = 2000;
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	#pragma region Enemies

	if (type == 1)
	{
		//worm
		sprites->Add(2021, 172, 412, 190, 422, texEnemy);
		sprites->Add(2022, 191, 412, 208, 422, texEnemy);

		sprites->Add(2023, 64, 412, 82, 422, texEnemy);
		sprites->Add(2024, 46, 412, 63, 422, texEnemy);

		ani = new CAnimation(100);
		ani->Add(2021);
		ani->Add(2022);
		animations->Add(204, ani);

		ani = new CAnimation(100);
		ani->Add(2023);
		ani->Add(2024);
		animations->Add(205, ani);

		//dome
		sprites->Add(2051, 149, 424, 167, 442, texEnemy);
		sprites->Add(2052, 169, 424, 187, 442, texEnemy);

		sprites->Add(2053, 187, 441, 205, 459, texEnemy);
		sprites->Add(2054, 187, 461, 205, 479, texEnemy);

		sprites->Add(2055, 169, 479, 187, 497, texEnemy);
		sprites->Add(2056, 149, 479, 167, 497, texEnemy);

		sprites->Add(2057, 132, 461, 150, 479, texEnemy);
		sprites->Add(2058, 132, 441, 150, 459, texEnemy);

		ani = new CAnimation(100);
		ani->Add(2051);
		ani->Add(2052);
		animations->Add(210, ani); //walking normal

		ani = new CAnimation(100);
		ani->Add(2053);
		ani->Add(2054);
		animations->Add(211, ani); //walking down

		ani = new CAnimation(100);
		ani->Add(2055);
		ani->Add(2056);
		animations->Add(212, ani);//walking upside down

		ani = new CAnimation(100);
		ani->Add(2057);
		ani->Add(2058);
		animations->Add(213, ani);//walking up

		//floater
		sprites->Add(2031, 84, 407, 102, 422, texEnemy);
		sprites->Add(2032, 104, 406, 122, 422, texEnemy);

		sprites->Add(2033, 152, 407, 170, 422, texEnemy);
		sprites->Add(2034, 132, 406, 150, 422, texEnemy);

		ani = new CAnimation(100);
		ani->Add(2031);
		ani->Add(2032);
		animations->Add(206, ani);

		ani = new CAnimation(100);
		ani->Add(2033);
		ani->Add(2034);
		animations->Add(207, ani);

		//jumper
		sprites->Add(2001, 132, 499, 149, 525, texEnemy);
		sprites->Add(2002, 152, 499, 167, 525, texEnemy);
		sprites->Add(2003, 170, 499, 185, 525, texEnemy);

		sprites->Add(2004, 105, 499, 122, 525, texEnemy);
		sprites->Add(2005, 87, 499, 102, 525, texEnemy);
		sprites->Add(2006, 69, 499, 84, 525, texEnemy);

		ani = new CAnimation(100);
		ani->Add(2001);
		ani->Add(2002);
		ani->Add(2003);
		animations->Add(200, ani); //walking toward right

		ani = new CAnimation(100);
		ani->Add(2004);
		ani->Add(2005);
		ani->Add(2006);
		animations->Add(201, ani); //walking toward left

		//insect
		sprites->Add(2041, 132, 530, 150, 548, texEnemy);
		sprites->Add(2042, 152, 533, 170, 548, texEnemy);

		sprites->Add(2043, 104, 530, 122, 548, texEnemy);
		sprites->Add(2044, 84, 533, 102, 548, texEnemy);

		ani = new CAnimation(300);
		ani->Add(2041);
		ani->Add(2042);
		animations->Add(208, ani);

		ani = new CAnimation(300);
		ani->Add(2043);
		ani->Add(2044);
		animations->Add(209, ani);

		//orb
		sprites->Add(2061, 158, 387, 176, 405, texEnemy);
		sprites->Add(2062, 98, 387, 116, 405, texEnemy);
		sprites->Add(2063, 118, 387, 136, 405, texEnemy);
		sprites->Add(2064, 138, 387, 156, 405, texEnemy);
		sprites->Add(2065, 78, 387, 96, 405, texEnemy);

		ani = new CAnimation(200);
		ani->Add(2061);
		ani->Add(2062);
		ani->Add(2063);
		ani->Add(2064);
		animations->Add(214, ani);

		ani = new CAnimation(200);
		ani->Add(2065);
		ani->Add(2064);
		ani->Add(2063);
		ani->Add(2062);
		animations->Add(215, ani);

		//bomber
		sprites->Add(2011, 194, 530, 212, 548, texEnemy);
		sprites->Add(2012, 174, 527, 192, 548, texEnemy);

		sprites->Add(2013, 42, 530, 60, 548, texEnemy);
		sprites->Add(2014, 62, 527, 80, 548, texEnemy);


		//bomber
		ani = new CAnimation(100);
		ani->Add(2011);
		ani->Add(2012);
		animations->Add(202, ani);

		ani = new CAnimation(100);
		ani->Add(2013);
		ani->Add(2014);
		animations->Add(203, ani);
	}
	else if (type == 2)
	{
		//eyeball
		sprites->Add(2067, 102, 550, 118, 566, texEnemy);
		sprites->Add(2068, 136, 550, 152, 566, texEnemy);
		sprites->Add(2069, 119, 550, 135, 566, texEnemy);
		ani = new CAnimation(100);
		ani->Add(2069);
		ani->Add(2068);
		animations->Add(217, ani);

		ani = new CAnimation(100);
		ani->Add(2069);
		ani->Add(2068);
		animations->Add(218, ani);

		//cannon
		sprites->Add(2070, 132, 603, 158, 629, texEnemy);
		sprites->Add(2071, 162, 603, 184, 629, texEnemy);
		sprites->Add(2072, 187, 607, 213, 629, texEnemy);
		ani = new CAnimation(600);
		ani->Add(2070);
		ani->Add(2071);
		ani->Add(2072);
		animations->Add(219, ani);

		//tele
		sprites->Add(2073, 132, 568, 156, 600, texEnemy);
		sprites->Add(2074, 159, 568, 183, 600, texEnemy);
		ani = new CAnimation(300);
		ani->Add(2074);
		ani->Add(2073);
		animations->Add(220, ani);
	}
	#pragma endregion Add Texture
	#pragma region Map
	for (size_t i = 0; i < WMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer* layer = WMap->GetTileLayer(i);
		if (layer->IsVisible() == true)
		{
			int tileWidth = WMap->GetTileWidth();
			int tileHeight = WMap->GetTileHeight();

			for (size_t n = 0; n < layer->GetHeight(); n++)
			{
				for (size_t m = 0; m < layer->GetWidth(); m++)
				{
					int tilesetIndex = layer->GetTileTilesetIndex(m, n);
					int tileID = layer->GetTileId(m, n);
					if (tilesetIndex != -1 && tileID != 406)
					{
						int y = tileID / 11;
						int x = tileID - y * 11;

						int left = x * tileWidth;
						int top = y * tileHeight;
						int right = left + tileWidth;
						int bottom = top + tileHeight;
						sprites->Add(id, left, top, right, bottom, texMap);

						float pos_X = (float)(m * tileWidth /*+ tileWidth / 2*/);
						float pos_Y = (float)(2032 - (n * tileHeight)/* + tileHeight / 2*/);
						//if (pos_Y < 100.0f && (pos_X>=16.0f && pos_X<=400.0f))
						//{
						UnmovingObject* item = new UnmovingObject();
						item->SetPos(pos_X, pos_Y);
						item->SetLayer(i);
						item->Add_Image(id);
						ListMapItem.push_back(item);
						//}
						id++;
					}
				}
			}
		}
	}
	#pragma endregion Add Tiles of Map
	#pragma region Object
	for (size_t i = 0; i < WMap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup* objectGroup = WMap->GetObjectGroup(i);

		//Add objects for Collision
		if (objectGroup->GetName() == "UnMVObj")
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* object = objectGroup->GetObjects().at(j);
				UnmovingObject* item = new UnmovingObject();
				item->SetPos(object->GetX(),
					2032.0f - object->GetY());
				sprites->Add(id, item->Get_x(), item->Get_y(),
					item->Get_x() + object->GetWidth(), item->Get_y() + object->GetHeight(),
					CTextures::GetInstance()->Get(ID_TEX_TEST));
				item->Add_Image(id);
				item->SetLayer(OBJECT_GROUP);
				ListMapItem.push_back(item);
				id++;
			}
		}

		//Add objects to catch changing scenes
		if (objectGroup->GetName() == "Scenedoor")
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* object = objectGroup->GetObjects().at(j);
				UnmovingObject* item = new UnmovingObject();
				item->SetPos(object->GetX(),
					2032.0f - object->GetY());
				sprites->Add(id, item->Get_x(), item->Get_y(),
					item->Get_x() + object->GetWidth(), item->Get_y() + object->GetHeight(),
					CTextures::GetInstance()->Get(ID_TEX_TEST));
				item->Add_Image(id);
				int input = SCENE_DOOR;
				if (object->GetId() == 358 || object->GetId()==81) input = SPECIAL_DOOR1;
				else if (object->GetId() == 369) input = SPECIAL_DOOR2;
				item->SetLayer(input);
				ListMapItem.push_back(item);
				id++;
			}
		}

		//Add enemies

		if (type == 1)
		{
			////Worm
			if (objectGroup->GetName() == "Worm")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Worm* worm = new Enemy_Worm(object->GetX(), 2032.0f - object->GetY(), -0.03f, 0.0f, 40.0f);
					worm->Add_Image(204);
					worm->Add_Image(205);
					worm->SetId(idEnemy);
					worm->SetLayer(ENEMIES_WITH_TARGET);
					ListMapItem.push_back(worm);
					idEnemy++;
				}
			}

			//Dome
			if (objectGroup->GetName() == "Dome")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Dome* dome = new Enemy_Dome(object->GetX(), 2032.0f - object->GetY()
						, -0.02f, 0.02f, 30.0f, 100.0f, true);
					dome->Add_Image(210);
					dome->Add_Image(211);
					dome->Add_Image(212);
					dome->Add_Image(213);
					dome->SetId(idEnemy);
					dome->SetLayer(ENEMIES_WITH_TARGET);
					ListMapItem.push_back(dome);
					idEnemy++;
				}
			}

			////Floater
			if (objectGroup->GetName() == "Floater")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Floater* floater = new Enemy_Floater(object->GetX(), 2032.0f - object->GetY()
						, object->GetId() %2==1 ? 0.018f : -0.018f ,-0.018f, 30.0f, 30.0f);
					floater->Add_Image(206);
					floater->Add_Image(207);
					floater->SetId(idEnemy);
					floater->SetLayer(ENEMIES_WITH_TARGET);
					ListMapItem.push_back(floater);
					idEnemy++;
				}
			}

			//Jumper
			if (objectGroup->GetName() == "Jumper")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Jumper* jumper= new Enemy_Jumper(object->GetX(), 2032.0f - object->GetY()
						, -0.018f, 50.0f);
					jumper->Add_Image(200);
					jumper->Add_Image(201);
					jumper->SetId(idEnemy);
					jumper->SetLayer(ENEMIES_WITH_TARGET);
					ListMapItem.push_back(jumper);
					idEnemy++;
				}
			}

			//Insect
			if (objectGroup->GetName() == "Insect")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Insect* insect = new Enemy_Insect(object->GetX(), 2032.0f - object->GetY()
						, -0.01f,-0.015f, 40.0f,40.0f);
					insect->Add_Image(208);
					insect->Add_Image(209);
					insect->SetId(idEnemy);
					insect->SetLayer(ENEMIES_WITHOUT_TARGET);
					ListMapItem.push_back(insect);
					idEnemy++;
				}
			}

			//Orb
			if (objectGroup->GetName() == "Orb")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Orb* Orb = new Enemy_Orb(object->GetX(), 2032.0f - object->GetY()
						, object->GetId()%2==0 ?-0.05f:0.05f, 0, 55.0f, 40.0f);
					Orb->Add_Image(214);
					Orb->Add_Image(215);
					Orb->SetId(idEnemy);
					Orb->SetLayer(ENEMIES_WITHOUT_TARGET);
					ListMapItem.push_back(Orb);
					idEnemy++;
				}
			}

			//Bomber
			if (objectGroup->GetName() == "Bomber")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Bomber* Bomber = new Enemy_Bomber(object->GetX(), 2032.0f - object->GetY()
						, -0.02f, 0, 20.0f, 40.0f);
					Bomber->Add_Image(202);
					Bomber->Add_Image(203);
					Bomber->SetId(idEnemy);
					Bomber->SetLayer(ENEMIES_WITH_TARGET);
					ListMapItem.push_back(Bomber);
					idEnemy++;
				}
			}
		}
		else if (type == 2)
		{
			//EyeBall
			if (objectGroup->GetName() == "EyeBall")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
				Tmx::Object* object = objectGroup->GetObjects().at(j);
				Enemy_EyeBall* floater = new Enemy_EyeBall(object->GetX(), 2032.0f - object->GetY()
					, object->GetId() % 2 == 1 ? 0.018f : -0.018f, object->GetId() % 2 == 1 ?-0.01f:0.01f, 50.0f, 40.0f);
				floater->Add_Image(217);
				floater->Add_Image(218);
				floater->SetId(idEnemy);
				floater->SetLayer(ENEMIES_WITH_TARGET);
				ListMapItem.push_back(floater);
				idEnemy++;
				}
			}

			//Tele
			if (objectGroup->GetName() == "Tele")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Teleporter* tele =new Enemy_Teleporter(object->GetX(), 2032.0f - object->GetY()
						, object->GetId() % 2 == 1 ? 0.1f : 0.0f, object->GetId() % 2 == 0 ? 0.1f : 0.0f,100.0f,100.0f);
					tele->Add_Image(220);
					tele->SetId(idEnemy);
					tele->SetLayer(ENEMIES_WITH_TARGET);
					ListMapItem.push_back(tele);
					idEnemy++;
				}
			}

			//Cannon
			if (objectGroup->GetName() == "Cannon")
			{
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* object = objectGroup->GetObjects().at(j);
					Enemy_Cannon* cannon = new Enemy_Cannon(object->GetX(), 2032.0f - object->GetY());
					cannon->Add_Image(219);
					cannon->SetId(idEnemy);
					cannon->SetLayer(ENEMIES_WITHOUT_TARGET);
					ListMapItem.push_back(cannon);
					idEnemy++;
				}
			}
		}
	}
	#pragma endregion Add Objects to Map

}

Tmx::Map* WorldMap::GetMap()
{
	return WMap;
}

int WorldMap::GetWidth()
{
	return WMap->GetWidth() * 16;
}

int WorldMap::GetHeight()
{
	return WMap->GetHeight() * 16;
}

int WorldMap::GetTileWidth()
{
	return WMap->GetTileWidth();
}

int WorldMap::GetTileHeight()
{
	return WMap->GetTileHeight();
}

GameObject* WorldMap::FindById(int id)
{
	for (UINT i = 0; i < ListMapItem.size(); i++)
	{
		if (ListMapItem[i]->GetId() == id)
			return ListMapItem[i];
	}
	return NULL;
}
