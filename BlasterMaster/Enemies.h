#pragma once
#include "GameObject.h"
#include "Item.h"
#include "Sound.h"

class Enemy : public MovingObject
{
protected:
	float x_end;
	float y_end;
	float x_start;
	float y_start;

	//float lastvx;
	bool DrawCenter = false;
	int transparentcy = 255;
public:
	 Enemy(float x = 0, float y = 0, float vx=0,float vy=0, float limited_move_x = 0, float limited_move_y = 0,bool DrawCenter=false)
		:MovingObject(x, y,vx,vy) {
		 this->x_end = limited_move_x + x; this->y_end = -limited_move_y + y; 
		 this->x_start = x-limited_move_x; this->y_start = y; 
		 this->DrawCenter = DrawCenter; this->HealthPoint = 3;
		 this->ClassEnemy = 0;
	}
	virtual void Update(DWORD dt,vector<GameObject*> *coOBject);
	void DropItem();
	void SetTransparentcy(int tprtc) { this->transparentcy = tprtc; }
	void Render();
};
class CAC_Enemy : public Enemy //Change Animations Constantly
{
public:
	CAC_Enemy(float x = 0, float y = 0, float vx = 0,float vy=0, float limited_move_x = 0,float limited_move_y=0, bool DrawCenter = false)
		:Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		this->designatedFrame = -1;
	};
	void Update(DWORD dt, vector<GameObject*>* coOject);
};

class CAWA_Enemy : public Enemy //Change Animations While Attacking
{
public:
	CAWA_Enemy(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		this->designatedFrame = 0;
	};
};

class Enemy_Dome : public CAC_Enemy
{
protected:
	bool FlagFalling = false;
	bool FlagAttack = false;
	bool FlagUseless = false;
	float holdtimer = 0;
	float vtHold = 0.0f;
public:
	Enemy_Dome(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		vy > 0 ? this->currentAni = 2 : this->currentAni = 0;
	}
	void Update(DWORD dt, vector<GameObject*>* coOBject, float x_target, float y_target);
};

class Enemy_Jumper : public CAC_Enemy
{
public:
	Enemy_Jumper(float x = 0, float y = 0, float vx = 0, float limited_move_x=0, bool DrawCenter=false) 
		:CAC_Enemy(x, y, vx, NULL, limited_move_x, NULL, DrawCenter) {}
	void Update(DWORD dt, vector<GameObject*>* coOBject,float x_target,float y_target);
};

class Enemy_Worm : public CAC_Enemy
{
public:
	Enemy_Worm(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, vy, limited_move_x, NULL, DrawCenter) {
	}
	void Update(DWORD dt, vector<GameObject*>* coOBject,float x_target,float y_target);
};

class Enemy_Insect : public CAC_Enemy
{
public:
	Enemy_Insect(float x = 0, float y = 0,float vx=0,float vy=0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt, vector<GameObject*>* coOBject);
};

class Enemy_Orb : public CAC_Enemy
{
protected:
	float prevX;
public:
	Enemy_Orb(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		vx < 0 ? currentAni = 1 : currentAni = 0;
	}
	void Update(DWORD dt, vector<GameObject*>* coOBject/*, float x_target, float y_target*/);
};

class Enemy_Teleporter : public CAWA_Enemy
{
protected:
	bool FlagFinish = false;
	bool FlagSetTo0 = false;
	float timerCD = -1;
	float vtCD = 0;
	float distance = 0;
	float prevpos = 0;
	float tempSpeedX = 0;
	float tempSpeedY = 0;
public:
	Enemy_Teleporter(float x = 0, float y = 0,float vx=0,float vy=0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, 0, 0, limited_move_x, limited_move_y, DrawCenter) {
		tempSpeedX = vx;
		tempSpeedY = vy;
	}
	void Update(DWORD dt, vector<GameObject*>* coOBject, float x_target, float y_target);
	void HP_down(int down=1) { if (designatedFrame == 1) HealthPoint-=down; }
};