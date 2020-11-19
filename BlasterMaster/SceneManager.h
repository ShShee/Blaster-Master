#pragma once
#include "Scene.h"
#include "OverWorldScene.h"
class SceneManager
{
private:
	static SceneManager *_instance;
	vector<Scene*> ListScene;
	int currentScene=1;
public:

	SceneManager();
	static SceneManager* GetInstance();

	Scene* GetCurrentScene();
	KeyEventHandler* GetKeyEventHandler();

	void LoadContent();
	void Update(DWORD dt);
	void Render();
};

