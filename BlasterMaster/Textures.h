#pragma once
#include <unordered_map>
#include <d3dx9.h>

#define ID_TEX_TEST 100
#define ID_TEX_SOPHIA 0
#define ID_TEX_JASON 1
#define ID_TEX_ITEM 5
#define ID_TEX_ENEMY 10
#define ID_TEX_BOSS 15
#define ID_TEX_TILESET 20
#define ID_TEX_HEALTHBAR 30
#define ID_TEX_ENDING 35
#define ID_TEX_LIFE 38
#define ID_TEX_PLAY 39
#define ID_TEX_OPENING 40
#define ID_TEX_INTRO 41

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures* __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextures* GetInstance();
};
