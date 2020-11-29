#include "Jason.h"

void Jason::Update(DWORD dt, vector<GameObject*>* coObject)
{
	ControllableChar::Update(dt, coObject);
	if(FlagClimbing==false || (FlagClimbing==true && *status!=NOTHING)) vy -= 0.03f;\

	lastX = x;
	((lastY < y || lastY - 30.0f>y) && LockCam(lastX, lastY) == false) ? lastY = y : lastY = lastY;
	CGame::GetInstance()->SetCamPos(lastX - 150.0f, lastY + 150.0f);
}

void Jason::Render()
{
	//RenderBoundingBox();
	bool flipX = false;
	if (currentAni % 2 == 0 || lastAni % 2 == 0) flipX = true;
	if (currentAni >= 0 && designatedFrame == -1)
	{
		animations[currentAni]->Render(x, y, -1, true, flipX,RenderColor);
	}
	else
	{
		animations[lastAni]->Render(x, y, designatedFrame, true, flipX,RenderColor);
	}
}

void Jason::SetAni(int ani)
{
	designatedFrame = 0;
	switch (ani)
	{
	case GO_RIGHT:
		if (*status == LYING) ani = 4; else { ani = 2; y += 0.5f; }
		vx = 0.1f;
		designatedFrame = -1;

		break;
	case GO_LEFT:
		if (*status == LYING) ani = 5; else { ani = 3; y += 0.5f; }
		vx = -0.1f;
		designatedFrame = -1;
		break;
	case GO_UP:
		if (*status == LYING)
		{
			*status = NOTHING;
			if (lastAni == 4) ani = 0; else ani = 1;
			y += 10.0f;
		}
		else if (FlagClimbing == true && *status==NOTHING)
		{
			ani = 6;
			vy = 0.04f;
			designatedFrame = -1;
			FlagClimbing = false;
		}
		else ani = -1;
		break;
	case GO_DOWN:
		if (*status == NOTHING && FlagClimbing==false)
		{
			*status = LYING;
			if (lastAni == 0) ani = 4; else ani = 5;
			y -= 5.0f;
		}
		else if (FlagClimbing == true && *status == NOTHING)
		{
			ani = 6;
			vy = -0.04f;
			designatedFrame = -1;
			FlagClimbing = false;
		}
		else ani = -1;
		break;
	case JUMP:
		if (*status == NOTHING)
		{
			*status = JUMPING;
			IsFalling = true;
			vx = 0; vy = +0.2f;
			designatedFrame = 2;
			if (lastAni % 2 == 0) ani = 2; else ani = 3;
		}
		else ani = -1;
		break;
	case FIRE:
		ani = lastAni;
		if (timerCD <= 0)
		{
			if (ani == 0 || ani == 2) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x + 4.0f, y - 8.0f, 0.3f, 0.0f, false, 3);
			else if (ani == 1 || ani == 3) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x + 4.0f, y - 8.0f, -0.3f, 0.0f, false, 4);
			else if (ani == 4) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x + 7.5f, y - 5.0f, +0.3f, 0.0f, false, 3);
			else if (ani == 5) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x + 7.5f, y - 5.0f, -0.3f, 0.0f, false, 4);
			BulletFired++;
			if (BulletFired > 2)
			{
				timerCD = 100.0f; BulletFired = 0;
			}
			else timerCD = 0.0f;
			vtCD = 0.0f;
		}
		else vtCD = 0.5f;
		break;
	case IDLE:
		vx = 0;
		if (IsFalling == true) designatedFrame = 2;
		if (lastAni == 2 && *status == NOTHING) ani = 0;
		else if (lastAni == 3 && *status == NOTHING) ani = 1;
		if (FlagClimbing == true && *status==NOTHING) ani = 6;
		if (lastAni != 6) y += 0.5f; else vy = 0;
		break;
	}
	if (ani != lastAni && ani >= 0)
	{
		this->lastAni = ani;
	}
	if (ani < 0) ani = lastAni;
	MovingObject::SetAni(ani);
}


