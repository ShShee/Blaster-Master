#include "Boss.h"

Boss::Boss()
{
	GameObject::SetPos(850.0f, 1440.0f);
	HealthPoint = 13;
	vx = 0.016f;
	vy = 0.016f;
	x_start = this->x - 100.0f;
	x_end = this->x + 100.0f;
	y_end = this->y + 50.0f;
	y_start = this->y - 30.0f;
	layer = ENEMIES_WITHOUT_TARGET;

	Enemy* addHand;
	for (UINT i = 1; i < 6; i++)
	{
		addHand = new BossHand(x - 6.0f, y - 15.0f * i);
		LeftHand.push_back(addHand);

		addHand = new BossHand(x + 50.0f, y - 15.0f * i);
		RightHand.push_back(addHand);
	}
}

void Boss::Update(DWORD dt, vector<GameObject*>* coObject)
{
	wp.Update(dt, coObject);
	if (HealthPoint > 1)
	{
		if (timerAT < 2500)
		{
			timerAT += vtCD * dt;
			currentAni = 0;
			transparency = timerAT / 10;
			//for (UINT i = 0; i < 5; i++)
			//{
			//	LeftHand[i]->SetAni(0);
			//	RightHand[i]->SetAni(0);
			//}
		}
		else
		{
			CoolDown += vtCD * dt;
			for (UINT i = 1; i < 6; i++)
			{
				LeftHand[i - 1]->SetSpeed(this->vx - this->vx * i / 8, this->vy+this->vy*i/3);
				RightHand[i - 1]->SetSpeed(this->vx + this->vx * i / 8, this->vy + this->vy * i / 3);
			}
			Enemy::Update(dt, coObject);
			for (UINT i = 1; i < 6; i++)
			{
				LeftHand[i - 1]->Update(dt, coObject);
				RightHand[i - 1]->Update(dt, coObject);
			}
			if (x > x_end || x < x_start)
			{
				vx = -vx;
			}
			else if (y > y_end || y < y_start)
			{
				vy = -vy;
			}
			currentAni = 1;
			transparency = 255;
			for (UINT i = 0; i < 5; i++)
			{
				LeftHand[i]->SetAni(1);
				RightHand[i]->SetAni(1);
			}
			if (CoolDown >= 500)
			{
				wp.AddBullet(1, 0, x + 30.0f, y - 30.0f, 0, -0.08f, false, 5);
				bulletcount++;
				if (bulletcount < 3) CoolDown = 0; else { CoolDown = -2500; bulletcount = 0; }
			}
		}
	}
	else if(HealthPoint>0)
	{
		timerAT -= vtCD * dt;
		currentAni = 0;
		for (UINT i = 0; i < 5; i++)
		{
			LeftHand[i]->SetAni(0);
			RightHand[i]->SetAni(0);
		}
		transparency = timerAT / 10;
		if (timerAT < 0) HealthPoint--;
	}
}

void Boss::Render()
{
	animations[currentAni]->Render(x, y, designatedFrame, 0, false, RenderColor, transparency);
	wp.Render();
	for (UINT i = 0; i < 5; i++)
	{
		LeftHand[i]->SetTransparentcy(transparency);
		LeftHand[i]->Render();
		RightHand[i]->SetTransparentcy(transparency);
		RightHand[i]->Render();
	}
	if (HealthPoint == 1)
	{
		explosion->Render(x - 48.0f, y - 10.0f,-1,0,false,200,transparency);
		explosion->Render(x - 7.0f, y - 37.0f,- 1, 0, false, 200, transparency);
		explosion->Render(x + 11.0f, y - 14.0f, -1, 0, false, 200, transparency);
		explosion->Render(x + 43.0f, y - 23.0f,- 1, 0, false, 200, transparency);
		explosion->Render(x + 76.0f, y - 45.0f,- 1, 0, false, 200, transparency);
	}
}

void Boss::LoadContent()
{
	MovingObject::Add_Image(221);
	MovingObject::Add_Image(222);
	for (UINT i = 0; i < 4; i++)
	{
		LeftHand[i]->Add_Image(227);
		LeftHand[i]->Add_Image(223);
		RightHand[i]->Add_Image(229);
		RightHand[i]->Add_Image(225);
	}
	LeftHand[4]->Add_Image(228);
	LeftHand[4]->Add_Image(224);
	RightHand[4]->Add_Image(230);
	RightHand[4]->Add_Image(226);

	wp.AddBulletId(Boss_Bullet);
	wp.AddBulletId(751);

	explosion = CAnimations::GetInstance()->Get(751);
}

void BossHand::Update(DWORD dt, vector<GameObject*>* coObject)
{
	nx = 0; ny = 0;
	GameObject::Update(dt);
	coEvents.clear();
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() != 0)
	{
		float min_tx, min_ty;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	}

	x += dx;
	y += dy;

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<ControllableChar*>(e->obj)) // if e->obj is Enemies
		{
			if ((e->nx != 0 || e->ny != 0) && untouchable == 0)
			{
				e->obj->HP_down();
				e->obj->StartUntouchable();
				Sound::getInstance()->play("sophiahit", false, 1);
			}
		}
	}
}
