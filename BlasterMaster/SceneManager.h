#pragma once
#include "Scene.h"
#include "OverWorldScene.h"
#include "EndingScene.h"
#include "OpeningScene.h"

class SceneManager
{
private:
	static SceneManager *_instance;
	vector<Scene*> ListScene;
	int currentScene=3;

	//LPDIRECT3DTEXTURE9 texLife;
	float timer = 1000;
	float vt = 0;
	LPANIMATION Life;
	int lifeCount = 2;
public:

	SceneManager();
	static SceneManager* GetInstance();

	Scene* GetCurrentScene();
	KeyEventHandler* GetKeyEventHandler();

	void LoadContent();
	void Update(DWORD dt);
	void Render();
};

