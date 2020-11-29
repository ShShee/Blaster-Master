#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Sprites.h"
#include <algorithm>
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"

#define BACKGROUND_LAYER 0
#define MAIN_LAYER 1
#define DOOR_LAYER 2
#define ITEM_LAYER 3
#define SPECIAL_DOOR1 4
#define SPECIAL_DOOR2 5
#define SCENE_DOOR 6
#define BOSS_DOOR 7
#define OBJECT_GROUP 8
#define ENEMIES_WITH_TARGET 9
#define ENEMIES_WITHOUT_TARGET 10
#define LADDER 11
#define TRAP 12

//drop state
#define HVNT_DROP_YET 0
#define DROPPED 1
#define DNT_DROP 2
#define PICKED 3

enum REACTION
{
	IDLE = -1,
	GO_RIGHT,
	GO_LEFT,
	GO_UP,
	GO_DOWN,
	JUMP,
	FIRE,
	GET_OUT,
	GET_IN,
	CHANGE
};

enum STATE
{
	NOTHING,
	LYING,
	JUMPING,
	LOOKUP,
};

using namespace std;

class GameObject;

struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;
struct CollisionEvent
{
	GameObject* obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, GameObject* obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

typedef GameObject * LPGAMEOBJECT;


class GameObject
{
protected:
	int id;

	float x;
	float y;

	float lastY;
	float lastX;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx = 0; //indicate moving speed
	float vy = 0; //indicate falling speed

	float nx, ny;
	int RenderColor=255;  //indicate being hit

	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	int layer=-1;
	int ClassEnemy = -1;
	int DropItemState = HVNT_DROP_YET;
	int IdItemDropped=-1;
	int HealthPoint=1;

	int untouchable;
	DWORD untouchable_start;

	DWORD dt;
public:

	GameObject(float x = 0, float y = 0) { this->x = this->lastX = x, this->y = this->lastY = y; this->untouchable = 0; this->id = 0; }
	void SetPos(float x, float y) { this->x =this->lastX= x; this->y=this->lastY = y; }

	virtual void Add_Image(int ID){}
	//virtual void Update(DWORD dt) { this->dt = dt; }
	virtual void Update(DWORD dt, vector<GameObject*> *coObject = NULL);
	virtual void Update(DWORD dt, vector<GameObject*> *coObject,float x_target,float y_target){}
	void UpdateCollision(vector<GameObject*>* coObject);
	virtual void DropItem(){}
	virtual void Render()=0;
	virtual void RenderBoundingBox()=0;

	virtual BoundingBox* GetBoundingBox() = 0;
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	CollisionEvent* SweptAABBEx(GameObject* coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<CollisionEvent*> &coEvents,
		vector<CollisionEvent*> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	float Get_x() { return x; }
	float Get_y() { return y; }
	float Get_lastx() { return lastX; }
	float Get_lasty() { return lastY; }
	float Get_vx() { return vx; }
	float Get_vy() { return vy; }
	virtual bool IsAbletoMove() = 0;
	void HP_up(int up=1) { HealthPoint+=up; }
	virtual void HP_down(int down=1) { HealthPoint-=down; }
	int GetHP() { return HealthPoint; }
	void SetLayer(int layer) { this->layer = layer; }
	int GetLayer() { return this->layer; }
	int GetClassEnemy() { return this->ClassEnemy; }
	void SetDropItemState(bool dis) { this->DropItemState = dis; }
	bool GetDropItemState() { return this->DropItemState; }
	int GetIdItemDroppped() { return this->IdItemDropped; }
	void SetId(int ID) { this->id = ID; }
	int GetId() { return this ->id; }
	void SetRenderColor(int rclr) { this->RenderColor = rclr; }
	~GameObject() {}
};

class MovingObject : public GameObject
{
protected:

	int currentAni=0; //
	int designatedFrame=-1;
	vector<LPANIMATION> animations; //sprites of object

public:
	MovingObject(float x = 0, float y = 0,float vx=0,float vy=0) 
		:GameObject(x, y) { this->vx= vx;this->vy= vy; }
	void Add_Image(int ID);
	virtual void Render() {}
	void RenderBoundingBox();

	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	virtual void SetAni(int ani) { this->currentAni = ani;}
	void SetDesignatedFrame(int df) { designatedFrame = df; }

	bool IsAbletoMove() { return true; }
	int GetAnimationSize() { return animations.size(); }
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
	virtual void Render();
	void RenderBoundingBox() 
	{
		if (GetLayer() == 6)
		{
			D3DXVECTOR3 p(x, y, 0);
			BoundingBox* rect = GetBoundingBox();

			LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_TEST);

			CGame::GetInstance()->Draw(x, y, bbox, rect->x, rect->y, rect->x + rect->width, rect->y + rect->height, false, false,255,255);
		}
	};

	virtual bool IsAbletoMove() { return false; }
	BoundingBox* GetBoundingBox();
	~UnmovingObject() {};
};