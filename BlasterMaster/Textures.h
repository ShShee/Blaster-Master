#pragma once
#include <unordered_map>
#include <d3dx9.h>

#define ID_TEX_JASONSOPHIA 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MAPTILE 20
#define ID_TEX_TILESET 30

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
