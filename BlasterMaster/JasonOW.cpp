#include "JasonOW.h"

void JasonOW::ResetLife()
{
	if(FlagBossFight==false) this->SetPos(120.0f, 120.0f);
	ControllableChar::ResetLife();
}

void JasonOW::Update(DWORD dt, vector<GameObject*>* coObject)
{
	ControllableChar::Update(dt, coObject);
	if (FlagBossFight == false)
	{
		lastX = x;
		lastY = y;
		CGame::GetInstance()->SetCamPos(lastX - 150.0f, lastY + 150.0f);
	}
}

void JasonOW::Render()
{
	//RenderBoundingBox();
	if (HealthPoint > 0)
	{
		bool flipX = false;
		if (currentAni == 0 || lastAni == 0) flipX = true;
		if (designatedFrame < 0)
		{
			animations[currentAni]->Render(x, y, -1, true, flipX,RenderColor);
		}
		else {
			animations[lastAni]->Render(x, y, designatedFrame, true, flipX,RenderColor);
		}
	}
	else
	{
		if(currentAni!=4)	currentAni = lastAni = 4;
		animations[currentAni]->Render(x, y, -1, true, false, 255);
		if (animations[currentAni]->GetCurrentFrame() == 4)
		{
			FlagDead = true;
			ResetLife();
		}
		//ResetLife();
	}
}

void JasonOW::SetAni(int ani)
{
	if (HealthPoint > 0)
	{
		designatedFrame = -1;
		if (FlagAutomatic == true)
		{
			ani = -1;
		}
		switch (ani)
		{
		case GO_RIGHT:
			vx = 0.1f; vy = 0;
			break;
		case GO_LEFT:
			vx = -0.1f; vy = 0;
			break;
		case GO_UP:
			vy = +0.1f; vx = 0;
			break;
		case GO_DOWN:
			vx = 0.0f; vy = -0.1f;
			break;
		case FIRE:
			ani = lastAni;
			if (timerCD <= 0)
			{
				if (ani == 0) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x + 12.0f, y - 14.0f, 0.3f, 0.0f, false, 0);
				else if (ani == 1) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x, y - 14.0f, -0.3f, 0.0f, false, 1);
				else if (ani == 2) WeaponType[curWeapon]->AddBullet(curWeapon, 1, x + 5.0f, y, +0.0f, 0.3f, false, 2);
				else if (ani == 3) WeaponType[curWeapon]->AddBullet(curWeapon, 1, x + 5.0f, y - 14.0f, 0.0f, -0.3f, false, 5);
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
			if (FlagAutomatic == false)
			{
				vx = 0; vy = 0;
				designatedFrame = 0;
				break;
			}
		}

		if (ani != lastAni && ani >= 0)
		{
			this->lastAni = ani;
		}
		else if (ani < 0) ani = lastAni;
		MovingObject::SetAni(ani);
	}
}