#pragma once
#include "ControllableChar.h"

class JasonOW : public ControllableChar
{
private:
	static JasonOW* _instance;
	int curNWlevel = 0; //current normal weapon level
	void ResetLife();
public:
	JasonOW() :ControllableChar() { timeCSlimit = 480; };

	void WeaponUpgrade() { curNWlevel++; }
	void Update(DWORD dt, vector<GameObject*>* coObject = NULL);
	void Render();
	void SetAni(int ani);
};

