#pragma once
#include "Scene.h"

class MainAreaKeyHandler : public KeyEventHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
class MainAreaScene :public Scene
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
public:
	MainAreaScene();

	void Update(DWORD dt);
	void LoadContent();
	void Render();

	bool HasBeenDeadYet();
};

