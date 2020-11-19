#pragma once

#include "../BlasterMaster/MapReader/Tmx.h.in"
#include "Sprites.h"
#include "GameObject.h"
#include "ControllableChar.h"
#include "Textures.h"
#include <vector>

class WorldMap
{
private:
	Tmx::Map* WMap;
	vector<GameObject*> ListMapItem;
	LPDIRECT3DTEXTURE9 texMap;
	LPDIRECT3DTEXTURE9 texEnemy;
	int type = 1;
public:
	WorldMap(){}
	void LoadMap(const char* filePath,int type=1);

	void SetEnemiesTexture();
	void SetListItem();
	Tmx::Map* GetMap();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	GameObject* FindById(int id);
	vector<GameObject*> GetListMapItem() { return this->ListMapItem; }
};

