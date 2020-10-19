#include "Enemies.h"


void Enemy::Update(DWORD dt)
{
	MovingObject::Update(dt);
	if ((vx > 0 && x >= x_end) || (x < x_start && vx < 0)) vx = -vx;
	if (vx < 0 && animations.size()>1)	currentAni = 1; else currentAni = 0;
}

void Enemy::Render()
{
	animations[currentAni]->Render(x, y, designatedFrame, DrawCenter);
}

void Enemy_Jumper::Update(DWORD dt,float x_target,float y_target)
{
	Enemy::Update(dt);
	vy -= 0.1f;
	if (y < y_start) 
	{
			vy = 0;
			y = y_start;
	}
	if ((x<x_target && x+20>x_target)|| (x > x_target && x - 20 < x_target)) if (y == y_end) vy = +/*gravity_effect*/0.4f;
}

void Enemy_Bomber::Update(DWORD dt,float x_target,float y_target)
{
	Enemy::Update(dt);
	if ((x<x_target && x + 40>x_target) || (x > x_target && x - 40 < x_target)) if (y == y_start) vy = +0.03f;
	if (y >= y_end) 
	{
		y = y_end; vy = 0.0f; vx = 0.0f;
	}
	if (vy > 0) designatedFrame = 1; else designatedFrame = 0;
}

void Enemy_Worm::Update(DWORD dt,float x_target,float y_target)
{
	Enemy::Update(dt);
	if (/*(*//*x - 20 <= x_target && */(x >=x_target && vx>0) || (x<=x_target && vx<0)/*|| x-10<=x_target*//*) && y==y_target*/) vx = -vx;
}

void Enemy_Floater::Update(DWORD dt)
{
	Enemy::Update(dt);
	if ((vy > 0 && y >= y_end) || (y < y_start && vy < 0)) vy = -vy;
}

void Enemy_Insect::Update(DWORD dt)
{
	vy += 0.001f;
	if (y >= y_end) vy = -0.06f;
	//if (y < y_start) vy = 0.01f;
	Enemy::Update(dt);
}

void Enemy_Dome::Update(DWORD dt,float x_target,float y_target)
{
	MovingObject::Update(dt);
	if (x >= x_end && y <= y_start) {
		currentAni = 3; vy = 0.1f; vx = 0;
		//if (x + 10 >= x_target && x_target > x && vx > 0) {
		//	vx = 0; vy = 0.2f;
		//}
	}
	if ((y >= y_end && x>=x_end)/* || (x < x_start && y < y_end && y>y_start)*/) {
		currentAni = 0; vx = -0.1f; vy = 0;
	}
	if (x <=x_start && y >= y_end) { 
		currentAni = 1; vy = -0.1f; vx = 0; 
		//if (y +10 >= y_target && y_target > y && vy > 0) {
		//	vy = 0; vx = -0.2f;
		//}
	}
	if ((x <= x_start && y<=y_start)/* || (x<x_end && y < y_end && y>y_start)*/) {
		currentAni = 2; vy = 0; vx = 0.1f;
		//if (x-2 <= x_target && x_target < x && vx < 0) {
		//	vx = 0; vy = -0.2f;
		//}
	}

	//if ((y >= y_end && vx>0)||(y< y_start && vx<0)) vx = -vx;
	//if ((vx > 0 && x < x_end)|| (/*vx <0 && */y>= y_end))
	//{
	//	x += vx * dt;
	//}
	//if ((vx > 0 && x >= x_end && y< y_end)||(x<=x_start && vx<0)) {
	//	y += vx * dt;
	//}
	//if (x<x_end && vx>0 && y<y_end)		currentAni = 0;
	//else if(x>= x_end && vx>0 && y< y_end) currentAni = 1;
	//else if (y >y_end && vx<0 && x< x_end && x>x_start) currentAni = 2;
	//else if (x<= x_start && vx < 0 && y < y_end) currentAni = 3;
}

void Enemy_Orb::Update(DWORD dt,float x_target,float y_target)
{
	if (vy == 0)
	{
		x += vx * dt;
		if (x < x_end && x> x_start)
			designatedFrame = 0;
		else
		{
			designatedFrame = -1;
			vx = 0;
			if (animations[currentAni]->GetCurrentFrame() == 3)
			{
				if (x >= x_end) vx = -0.01f; else vx = 0.01f;
				//animations[currentAni]->SetCurrentFrame(0);
				if (vx < 0) currentAni = 1; else currentAni = 0;
			}
		}
	}
	else
	{
		if ((vx > 0 && x >= x_end) || (x < x_start && vx < 0)) vx = -vx;
		if ((vy > 0 && y >= y_end) || (y < y_start && vy < 0)) vy = -vy;
		if (x_target < x_end && y_target < y_end)
		{
			currentAni = 2; designatedFrame = -1;
			if ((x >= x_target && vx>0)) x=x_target; else x += vx * dt;
			if ((y >= y_target && vy>0)) y=y_target; else y += vy * dt;
		}
	}
}

void Enemy_EyeBall::Update(DWORD dt)
{
	Enemy::Update(dt);
	if ((vy > 0 && y >= y_end) || (y < y_start && vy < 0)) vy = -vy;
}

void Enemy_Cannon::Update(DWORD dt)
{

}

void Enemy_Teleporter::Update(DWORD dt,float x_target,float y_target)
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
