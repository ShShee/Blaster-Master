#include "Enemies.h"

void Enemy::Update(DWORD dt, vector<GameObject*>* coOBject)
{
		nx = 0; ny = 0;
		GameObject::Update(dt);
		GameObject::UpdateCollision(coOBject);

		if (GetTickCount() - untouchable_start > 150)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
		if (untouchable != 0) RenderColor = 0; else RenderColor = 255;
}

void CAC_Enemy::Update(DWORD dt, vector<GameObject*>* coOject)
{
	Enemy::Update(dt, coOject);
	if (vx < 0 && animations.size()>1)	currentAni = 1; else currentAni = 0;
	if ((vx > 0 && x >= x_end) || (x < x_start && vx < 0)) vx = -vx;
	if (ny != 0) vy = 0;
}

void Enemy::DropItem()
{
	int Id_ItemDropped = ItemHolder::GetInstance()->GenerateItem(ClassEnemy);
	if (Id_ItemDropped != -1)
	{
		GameObject* DropItem = new Item();
		DropItem->SetPos(x, y + 4.0f);
		DropItem->Add_Image(Id_ItemDropped);
		IdItemDropped = ItemHolder::GetInstance()->AddItem(DropItem);
	}
	Id_ItemDropped != -1 ? DropItemState = DROPPED : DropItemState = DNT_DROP;
}

void Enemy::Render()
{
	if (HealthPoint > 0)
	{
		//RenderBoundingBox();
		animations[currentAni]->Render(x, y, designatedFrame, DrawCenter,false,RenderColor,transparentcy);
	}
}

void Enemy_Dome::Update(DWORD dt, vector<GameObject*>* coOBject, float x_target, float y_target)
{
	vector<GameObject*> RawcoObject;
	for (int i = 0; i < coOBject->size() - 1; i++)
	{
		RawcoObject.push_back(coOBject->at(i));
	}
	Enemy::Update(dt, &RawcoObject);
	holdtimer += vtHold * dt;

	if (x<x_start || x>x_end) vx = -vx;
	if (x_target  < x_end && x_target > x_start - 60.0f && currentAni == 2 && FlagAttack == false && FlagUseless == false)
	{
		vy = -0.15f;
		vx = 0;
		FlagAttack = true;
		FlagUseless = true;
	}
	else if (FlagAttack == true)
	{
		if (ny != 0)
		{
			vy = -0.02f;
			vx = -0.02f;
			currentAni = 0;
			FlagAttack = false;
		}
	}
	else if (FlagUseless == false)
	{
		if (nx == 0 && (currentAni == 3 || currentAni == 1) && holdtimer == 0)
		{
			vy = -(vy * 5);
			vx > 0 ? vx = 0.02f : vx = -0.02f;
			currentAni = 2;
			vtHold = 0.5f;
		}
		else if (ny == 0 && (currentAni == 0 || currentAni == 2) && holdtimer > 100)
		{
			vx > 0 ? currentAni = 1 : currentAni = 3;
			vy > 0 ? vy = 0.02f : vy = -0.02f;
			holdtimer = 0;
			vtHold = 0;
			FlagFalling = true;
			vx = -(vx * 5);
		}
		else if (nx != 0 && ny != 0)
		{
			if (FlagFalling == false)
			{
				vy = -vy;
				vx > 0 ? currentAni = 3 : currentAni = 1;
				vx = vx * 5;
			}
			else
			{
				vy > 0 ? currentAni = 2 : currentAni = 0;
				vx > 0 ? vx = -0.02f : vx = 0.02f;
				FlagFalling = false;
			}
		}
	}
}

void Enemy_Jumper::Update(DWORD dt, vector<GameObject*>* coOBject,float x_target,float y_target)
{
	
	CAC_Enemy::Update(dt,coOBject);
	if(vy!=0) vy -= 0.01f;
	if ((x<x_target && x + 20>x_target) || (x > x_target && x - 30 < x_target)) if (vy == 0)
	{
		vy = +0.1f;
	}
}

void Enemy_Worm::Update(DWORD dt, vector<GameObject*>* coOBject,float x_target,float y_target)
{
	CAC_Enemy::Update(dt,coOBject);
	//if (((x >= x_target && vx > 0) || (x <= x_target && vx < 0)) 
	//	&& x_target<x_end && x_target>x_start && RenderColor==255)
	//{
	//	vx = -vx;
	//}
	if (x_start-60.0f < x_target && x_target<x_end)
	{
		vy = -0.2f;
	}
}

void Enemy_Insect::Update(DWORD dt, vector<GameObject*>* coOBject)
{
	CAC_Enemy::Update(dt, coOBject);
	vy += 0.0008f;
	if ( y>y_start) vy = -0.04f;
}

void Enemy_Orb::Update(DWORD dt, vector<GameObject*>* coOBject/*,float x_target,float y_target*/)
{
		Enemy::Update(dt, coOBject);
		if (nx!=0)
		{
			prevX = vx;
			vx = 0;
		}
		if (vx==0)
		{
			vx = -prevX;
			vx < 0?currentAni = 1:currentAni = 0;		
		}
}

void Enemy_Teleporter::Update(DWORD dt, vector<GameObject*>* coOBject,float x_target,float y_target)
{
	timerCD -= vtCD * dt;
	if (x_target >= x_start && x_target <= x_end && timerCD<0)
	{
		vx = tempSpeedX; vy = tempSpeedY;
		Enemy::Update(dt, coOBject);
		if (tempSpeedX != 0)
		{
			if ((x>distance && FlagFinish==false)||x<prevpos)
			{
				tempSpeedX = -tempSpeedX;
				if (x < prevpos) FlagFinish = true;
			}
			else if ((x>distance && FlagFinish==true)||nx!=0)
			{
				vtCD = 0.5f;
				timerCD = 1000;
				vx = 0;
				FlagFinish = false;
				if (nx != 0) 
				{
					tempSpeedX = -tempSpeedX;
				}
			}
		}
		if (tempSpeedY != 0)
		{
			if ((y > distance && FlagFinish == false) || (y < prevpos))
			{
				tempSpeedY = -tempSpeedY;
				if (y < prevpos) FlagFinish = true;
			}
			else if ((y > distance && FlagFinish == true) || ny != 0)
			{
				vtCD = 0.5f;
				timerCD = 1000;
				vy = 0;
				FlagFinish = false;
				if (ny != 0)
				{
					tempSpeedY = -tempSpeedY;
				}
			}
		}
	}
	if (vx == 0 && vy == 0)
	{
		designatedFrame = 0;
		if (tempSpeedX == 0)
		{
			tempSpeedY > 0 ? distance = y + 30.0f, prevpos = y : distance = y, prevpos = y - 30.0f;
		}
		else if (tempSpeedY == 0)
		{
			tempSpeedX > 0 ? distance = x + 30.0f, prevpos = x : distance = x, prevpos = x - 30.0f;
		}
	}
	else designatedFrame = 1;
}

