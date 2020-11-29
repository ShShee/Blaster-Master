#include "GameObject.h"


void GameObject::Update(DWORD dt, vector<GameObject*>* coObject)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

void GameObject::UpdateCollision(vector<GameObject*> *coObject)
{
	coEvents.clear();
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	}
}

#pragma region Moving Object
void MovingObject::Add_Image(int ID)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(ID);
	animations.push_back(ani);
}

void MovingObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	BoundingBox* rect=GetBoundingBox();

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_TEST);

	CGame::GetInstance()->Draw(x, y, bbox, rect->x,rect->y,rect->x+rect->width,rect->y+rect->height, false,false,255,255);
}

BoundingBox* MovingObject::GetBoundingBox()
{
	return new BoundingBox(this->x, this->y,
		this->animations[currentAni]->GetWidth(), this->animations[currentAni]->GetHeight());
}
#pragma endregion Function

#pragma region Unmoving Object
void UnmovingObject::Add_Image(int ID)
{
	tile = CSprites::GetInstance()->Get(ID);
}

void UnmovingObject::Render()
{
	//RenderBoundingBox();
	if(HealthPoint>0)
	tile->Draw(x, y,0,false,RenderColor,255);
}

BoundingBox* UnmovingObject::GetBoundingBox()
{
	return new BoundingBox(this->x, this->y,
		this->tile->GetWidth(), this->tile->GetHeight());
}
#pragma endregion Function

#pragma region Collision Event
CollisionEvent* GameObject::SweptAABBEx(GameObject* coO)
{
	BoundingBox* sobbox;		// static object bbox
	BoundingBox* mobbox;		// moving object bbox
	float t, nx, ny;

	sobbox=coO->GetBoundingBox();

	// deal with moving object: m speed = original m speed - collide object speed
	float svx=coO->Get_vx(), svy=coO->Get_vy();

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy + sdy;

	mobbox = this->GetBoundingBox();

	CGame::SweptAABB(
		mobbox,
		dx, dy,
		sobbox,
		t, nx, ny);

	return new CollisionEvent(t, nx, ny, coO);
}

void GameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		CollisionEvent* e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
		delete e;
	}

	sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
	//sort(coEvents.begin(), coEvents.end(),);
}

void GameObject::FilterCollision(vector<CollisionEvent*> &coEvents, vector<CollisionEvent*> &coEventsResult, float &min_tx, float &min_ty, float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		CollisionEvent* c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}
#pragma endregion