#pragma once
#include "ControllableChar.h"
class Boss: public Enemy,public Enemy_With_Weapon
{
protected:
	vector<Enemy*> LeftHand;
	vector<Enemy*> RightHand;
	float timerAT = 0;
	float transparency;
	int bulletcount = 0;
	LPANIMATION explosion;
public:
	Boss();
	void Update(DWORD dt, vector<GameObject*> *coObject = NULL);
	void Render();
	void LoadContent();
	bool IsAttackable() { return !(timerAT < 2500); }
};

class BossHand :public Enemy
{
public:
	BossHand(float x,float y):Enemy(x,y){}
	void Update(DWORD dt, vector<GameObject*>* coObject = NULL);
};

