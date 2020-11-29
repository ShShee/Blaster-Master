#pragma once

#include "../BlasterMaster/MapReader/Tmx.h.in"
#include "Sprites.h"
#include "GameObject.h"
#include "ControllableChar.h"
#include "Textures.h"
#include "Item.h"

#include <vector>

class WorldMap
{
private:
	Tmx::Map* WMap;
	vector<GameObject*> ListMapItem;
	LPDIRECT3DTEXTURE9 texMap;
	LPDIRECT3DTEXTURE9 texEnemy;
	LPDIRECT3DTEXTURE9 texBoss;
	LPDIRECT3DTEXTURE9 texEnding;
	int type = 1;
public:
	WorldMap(){}
	void LoadMap(const char* filePath,int type=1);

	void SetListItem();
	Tmx::Map* GetMap();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	GameObject* FindById(int id);
	vector<GameObject*> GetListMapItem() { return this->ListMapItem; }
};

