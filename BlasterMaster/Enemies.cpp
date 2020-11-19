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
		animations[currentAni]->Render(x, y, designatedFrame, DrawCenter,false,RenderColor);
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
	/*else if( y<y_end)*/
	//if (y < y_start) vy = 0.01f;
}

void Enemy_Orb::Update(DWORD dt, vector<GameObject*>* coOBject/*,float x_target,float y_target*/)
{
	//if (vy == 0)
	//{
		Enemy::Update(dt, coOBject);
		if (/*(x < x_end && x> x_start)||*/nx==0)
			designatedFrame = 0;
		else /*if (nx!=0 || x>x_end || x<x_start)*/ if (nx!=0)
		{
			designatedFrame = -1;
			if (animations[currentAni]->GetCurrentFrame() == 3)
			{
				vx = -vx;
				//animations[currentAni]->SetCurrentFrame(0);
				if (vx < 0) currentAni = 1; else currentAni = 0;
			}
		}
	//}
	//else
	//{
	//	if ((vx > 0 && x >= x_end) || (x < x_start && vx < 0)) vx = -vx;
	//	if ((vy > 0 && y >= y_end) || (y < y_start && vy < 0)) vy = -vy;
	//	if (x_target < x_end && y_target < y_end)
	//	{
	//		currentAni = 2; designatedFrame = -1;
	//		if ((x >= x_target && vx>0)) x=x_target; else x += vx * dt;
	//		if ((y >= y_target && vy>0)) y=y_target; else y += vy * dt;
	//	}
	//}
}

void Enemy_Teleporter::Update(DWORD dt, vector<GameObject*>* coOBject,float x_target,float y_target)
{
	MovingObject::Update(dt);
	if ((x_target + 100.0f >= x && x_target <= x) || (x_target - 100.0f <= x && x_target >= x))
	{
		designatedFrame = 1;
		//if (x <= x_start && y<=y_start) {
		//	vx = 0.6f; vy = 0.0f;
		//}
		//if (x >= x_end && y<=y_start)
		//{
		//	x = x_end;
		//	if (flag == 0)
		//	{
		//		vx = -0.6f; vy = 0.0f;
		//		flag = 1;
		//	}
		//}
		//if (flag==1 && x>=x_end && y<=y_start)
		//{
		//	vy = 0.6f; vx = 0.0f;
		//}
		//if (x >= x_end && y >= y_end)
		//{
		//	y = y_end;
		//		if (flag == true)
		//		{
		//			vy = -0.6; vx = 0.0f;
		//			flag = false;
		//		}
		//}
		
	}
	else designatedFrame = 0;
}

