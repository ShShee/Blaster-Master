#pragma once
#include "MainAreaScene.h"
class OverWorldKeyHandler : public KeyEventHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
class OverWorldScene: public MainAreaScene
{
public:
	OverWorldScene();

	void Update(DWORD dt);
	void LoadContent();
};

