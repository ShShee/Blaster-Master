#pragma once
#include "MainAreaScene.h"
#include "Boss.h"

class OverWorldKeyHandler : public KeyEventHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
class OverWorldScene: public MainAreaScene
{
protected:
	Boss* FinalBoss;
	float timerBF=0;
	float vtBF=0;
public:
	OverWorldScene();

	void Update(DWORD dt);
	void LoadContent();
	void Render();
};

