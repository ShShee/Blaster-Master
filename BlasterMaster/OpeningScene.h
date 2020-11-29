#pragma once
#include "EndingScene.h"
class OpeningScene:public EndingScene
{
private:
	LPDIRECT3DTEXTURE9 texPlay;
	LPDIRECT3DTEXTURE9 texOpening;
	LPDIRECT3DTEXTURE9 texIntro;
protected:
	vector<LPANIMATION>IntroParts;
	int currentAni = 0;
	int locationX;
	int locationY;
public:
	OpeningScene();
	void Update(DWORD dt);
	void LoadContent();
	void Render();
};

