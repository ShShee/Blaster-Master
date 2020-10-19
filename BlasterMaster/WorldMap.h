#pragma once

#include "../BlasterMaster/MapReader/Tmx.h.in"
#include "Sprites.h"
#include "GameObject.h"
#include "Textures.h"
#include <vector>

class WorldMap
{
private:
	Tmx::Map* WMap;
	vector<GameObject*> ListMapItem;
	LPDIRECT3DTEXTURE9 texMap;
public:
	WorldMap();
	void LoadMap(const char* filePath);

	void SetListItem();
	Tmx::Map* GetMap();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	vector<GameObject*> GetListMapItem() { return this->ListMapItem; }
};

