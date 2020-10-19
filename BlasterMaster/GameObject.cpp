#include <d3dx9.h>
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

void MovingObject::Add_Image(int ID)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(ID);
	animations.push_back(ani);
}

void MovingObject::Update(DWORD dt)
{
	this->x += vx * dt;
	this->y += vy * dt;
}

BoundingBox* MovingObject::GetBoundingBox()
{
	return new BoundingBox(this->x, this->y,
		this->animations[currentAni]->GetWidth(), this->animations[currentAni]->GetHeight());
}

void UnmovingObject::Add_Image(int ID)
{
	tile = CSprites::GetInstance()->Get(ID);
}

void UnmovingObject::Update(DWORD dt)
{

}

void UnmovingObject::Render()
{
	tile->Draw(x, y);
}

BoundingBox* UnmovingObject::GetBoundingBox()
{
	return new BoundingBox(this->x, this->y,
		this->tile->GetWidth(), this->tile->GetHeight());
}

