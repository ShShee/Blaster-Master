#pragma once
#include "ControllableChar.h"

class Jason : public ControllableChar
{
public:
	Jason() :ControllableChar() { timeCSlimit = 660; }
	void Update(DWORD dt, vector<GameObject*>* coObject = NULL);
	void Render();
	void SetAni(int ani);
};

