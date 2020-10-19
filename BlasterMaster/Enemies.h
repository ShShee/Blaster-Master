#pragma once
#include "GameObject.h"
class Enemy : public MovingObject
{
protected:
	float x_end;
	float y_end;
	float x_start;
	float y_start;
	bool DrawCenter = false;
public:
	 Enemy(float x = 0, float y = 0, float vx=0,float vy=0, float limited_move_x = 0, float limited_move_y = 0,bool DrawCenter=false)
		:MovingObject(x, y,vx,vy) {
		 this->x_end = limited_move_x + x; this->y_end = limited_move_y + y; this->x_start = x; this->y_start = y; this->DrawCenter = DrawCenter;
	}
	virtual void Update(DWORD dt);
	void Render();
};
class CAC_Enemy : public Enemy //Change Animations Constantly
{
public:
	CAC_Enemy(float x = 0, float y = 0, float vx = 0,float vy=0, float limited_move_x = 0,float limited_move_y=0, bool DrawCenter = false)
		:Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		this->designatedFrame = -1;
	};
};

class CAWA_Enemy : public Enemy //Change Animations While Attacking
{
protected:
public:
	CAWA_Enemy(float x = 0, float y = 0, float vx = 0,float vy=0, float limited_move_x = 0,float limited_move_y=0, bool DrawCenter = false)
		:Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		this->designatedFrame = 0;
	};
};

class Enemy_Jumper : public CAC_Enemy
{
public:
	Enemy_Jumper(float x = 0, float y = 0, float vx = 0, float limited_move_x=0, bool DrawCenter=false) 
		:CAC_Enemy(x, y, vx, NULL, limited_move_x, NULL, DrawCenter) {}
	void Update(DWORD dt,float x_target,float y_target);
};

class Enemy_Worm : public CAC_Enemy
{
public:
	Enemy_Worm(float x = 0, float y = 0, float vx = 0,float vy=0, float limited_move_x = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, vy, limited_move_x, NULL, DrawCenter) {}
	void Update(DWORD dt,float x_target,float y_target);
};

class Enemy_Bomber : public CAWA_Enemy
{
public:
	Enemy_Bomber(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt,float x_target,float y_target);
};

class Enemy_Floater : public CAWA_Enemy
{
public:
	Enemy_Floater(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt);
};

class Enemy_Insect : public CAC_Enemy
{
public:
	Enemy_Insect(float x = 0, float y = 0,float vx=0,float vy=0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt);
};

class Enemy_Dome : public CAC_Enemy
{
public:
	Enemy_Dome(float x = 0, float y = 0, float vx = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, 0, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt,float x_target,float y_target);
};

class Enemy_Orb : public CAWA_Enemy
{
public:
	Enemy_Orb(float x = 0, float y = 0,float vx=0,float vy=0,float limited_move_x=0,float limited_move_y=0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, 0.08f, vy, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt,float x_target,float y_target);
};

class Enemy_EyeBall: public CAC_Enemy
{
public:
	Enemy_EyeBall(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt);
};

class Enemy_Cannon : public CAC_Enemy
{
public:
	Enemy_Cannon(float x = 0, float y = 0, bool DrawCenter = false)
		:CAC_Enemy(x, y, 0,0,0,0, DrawCenter) {}
	void Update(DWORD dt);
};

class Enemy_Teleporter : public CAWA_Enemy
{
protected:
	int flag=0;
public:
	Enemy_Teleporter(float x = 0, float y = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, 0, 0, limited_move_x, limited_move_y, DrawCenter) {}
	void Update(DWORD dt,float x_target,float y_target);
};