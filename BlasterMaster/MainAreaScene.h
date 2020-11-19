#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Game.h"
#include "Enemies.h"
#include "WorldMap.h"
#include "Quadtree.h"
#include "Item.h"
#include "Scene.h"
#include "MainPlayer.h"

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

class MainAreaKeyHandler : public KeyEventHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
class MainAreaScene:public Scene
{
private:
	void SwitchPlayer();

protected:
	bool ChangeSceneorNot();

	vector<GameObject*> ListObject;
	vector<GameObject*> DoorLocation;

	MainPlayer* ReadyPlayer1;
	WorldMap* wm;
	Quadtree* quadtree;
	KeyEventHandler* keyHandler;
public:
	MainAreaScene();

	void Update(DWORD dt);
	void LoadContent();
	void Render();
	KeyEventHandler* GetKeyEventHandler() { return this->keyHandler; }
};

