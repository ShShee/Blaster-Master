#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Sprites.h"
#include "BoundingBox.h"

enum REACTION
{
	IDLE = -1,
	GO_RIGHT,
	GO_LEFT,
	GO_UP,
	GO_DOWN,
	JUMP
};

enum STATE
{
	NOTHING,
	LYING,
	JUMPING,
	LOOKUP,
	TURNAR
};

using namespace std;

class GameObject
{
protected:
	float x;
	float y;
public:

	GameObject(float x = 0, float y = 0) { this->x = x, this->y = y; }
	void SetPos(float x, float y) { this->x = x; this->y = y; }

	virtual void Add_Image(int ID){}
	virtual void Update(DWORD dt)=0;
	virtual void Update(DWORD dt,float x_target,float y_target){}
	virtual void Render()=0;

	virtual BoundingBox* GetBoundingBox() = 0;

	float Get_x() { return x; }
	float Get_y() { return y; }
	virtual bool IsAbletoMove() = 0;
	~GameObject() {}
};

class MovingObject : public GameObject
{
protected:
	float vx=0; //indicate moving speed
	float vy = 0; //indicate falling speed

	int currentAni=0; //
	int designatedFrame;
	vector<LPANIMATION> animations; //sprites of object

public:
	MovingObject(float x = 0, float y = 0,float vx=0,float vy=0) 
		:GameObject(x, y) { this->vx= vx;this->vy= vy; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void Add_Image(int ID);
	virtual void Update(DWORD dt);
	virtual void Render() {}
	virtual void SetAni(int ani) { this->currentAni = ani;}

	bool IsAbletoMove() { return true; }
	int GetCurAni() { return this->currentAni; }
	BoundingBox* GetBoundingBox();
	~MovingObject() {}
};

class UnmovingObject : public GameObject
{
protected:
	LPSPRITE tile; //sprite of object
public:
	UnmovingObject(float x = 0, float y = 0) :GameObject(x, y) {}
	void Add_Image(int ID);
	void  Update(DWORD dt);
	void Render();
	bool IsAbletoMove() { return false; }
	BoundingBox* GetBoundingBox();
	~UnmovingObject() {};
};

