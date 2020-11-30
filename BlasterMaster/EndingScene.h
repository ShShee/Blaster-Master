#pragma once
#include "Scene.h"

class NextKeyHandler : public KeyEventHandler
{
public:
	virtual void KeyState(BYTE* states){}
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode){}
};
class EndingScene: public Scene
{
private:
	bool FlagTheEnd = false;
	float location=0;
	float lag = 1986.0f;
	MovingObject* SmallDetails;
	MovingObject* frog;
	WorldMap* wm;
	Quadtree* quadtree;
	vector<GameObject*> ListObject;
protected:	
	float timer = -1000;
	float vt = 0.5f;
public:
	EndingScene();
	void Update(DWORD dt);
	void LoadContent();
	void Render();
};

