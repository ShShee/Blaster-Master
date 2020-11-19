#pragma once
#include "ControllableChar.h"

class Sophia : public ControllableChar
{
protected:
	int lastFrame = 0;
	float timerRU = 0; //timer reverse up
	float vtRU;
	float timerOH; //timer open hatch
	float vtOH;
	float Hoverlv = 0.03f;
	bool IsJasonOut = false;
	bool HasBeenUp = 0;

	void ResetLife();
public:
	Sophia() :ControllableChar() { timeCSlimit = 660; }

	void HoverUpgrade() { Hoverlv -= 0.01f; }
	void Update(DWORD dt, vector<GameObject*>* coObject = NULL);
	void Render();
	void SetAni(int ani);

	//bool GetJasonState() { return IsJasonBack; }
};
