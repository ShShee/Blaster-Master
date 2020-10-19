#include "WorldMap.h"

WorldMap::WorldMap()
{


	//RECT r;
	//r.left = 0;
	//r.top = 0;
	//r.right = this->GetWidth();
	//r.bottom = this->GetHeight();


}
void WorldMap::LoadMap(const char* filePath)
{
	WMap = new Tmx::Map();
	WMap->ParseFile(filePath);
	
	const Tmx::Tileset* tileset = WMap->GetTileset(0);
	//wstring stemp = s2ws(tileset->GetImage()->GetSource());
	//LPCWSTR result = stemp.c_str();
	CTextures::GetInstance()->Add(ID_TEX_TILESET, L"SpritesSource\\level2-side_bank.png", D3DCOLOR_XRGB(0, 255, 255));
	texMap = CTextures::GetInstance()->Get(ID_TEX_TILESET);
	// sprites->Add(4000, 160,0, 176, 16, texMap);
	
}
void WorldMap::SetListItem()
{
	int id = 3000;
	CSprites* sprites = CSprites::GetInstance();
	int layernum = WMap->GetNumTileLayers();
	//size_t	i = 0;
	//if (designatedLayer >= 0 && designatedLayer < layernum) 
	//{
	//	i = designatedLayer; layernum = i + 1;
	//}
	for (int i = 0; i < WMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer* layer = WMap->GetTileLayer(i);
		if (layer->IsVisible() == true)
		{
			int tileWidth = WMap->GetTileWidth();
			int tileHeight = WMap->GetTileHeight();

			for (int n = 0; n<layer->GetHeight(); n++)
			{
				for (int m = 0; m < layer->GetWidth(); m++)
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
						float pos_Y = (float)(2032-(n * tileHeight)/* + tileHeight / 2*/);

						UnmovingObject* item = new UnmovingObject();
						item->SetPos(pos_X, pos_Y);
						item->Add_Image(id);
						ListMapItem.push_back(item);
						id++;
					}
				}
			}
		}
	}
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
