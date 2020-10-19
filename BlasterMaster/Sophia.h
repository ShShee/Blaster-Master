#pragma once
#include "GameObject.h"
class Tire :public MovingObject
{
public:
	Tire(float x = 0, float y = 0, float vx = 0, float vy = 0) :MovingObject(x, y, vx, vy) { designatedFrame = 0; }
	void Update(DWORD dt);
	void Render();
};

class Core :public MovingObject
{
protected:
	bool isFlipRight = false;
public:
	Core(float x = 0, float y = 0, float vx = 0, float vy = 0) :MovingObject(x, y, vx, vy) { designatedFrame = -1; }
	virtual void Update(DWORD dt);
	virtual void Render();
};

class Turret :public Core
{
public:
	Turret(float x = 0, float y = 0, float vx = 0, float vy = 0) :Core(x, y, vx, vy) { designatedFrame = 0; }
	void Update(DWORD dt);
	void Render();
};

class Body :public Core
{
public:
	Body(float x = 0, float y = 0, float vx = 0, float vy = 0) :Core(x, y, vx, vy) { designatedFrame = 0; }
	void Update(DWORD dt);
	void Render();
};

class Sophia: public GameObject
{
private:
	float x;
	float y;
	//float vx = 0;
	//float vy = 0;
	Tire* tire1;
	Tire* tire2;
	Core* core;
	Body* body;
	Turret* turret;
public:
	Sophia(float x = 0, float y = 0/*, float vx = 0, float vy = 0*/);
	void SetSpeed(float vx = 0, float vy = 0);
	void Update(DWORD dt);
	void Add_Image(int idCore,int idTire1, int idTire2, int idBody, int idTurret);
	void Render();
};

