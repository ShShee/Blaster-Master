#include "Sophia.h"

void Sophia::ResetLife()
{
	this->SetPos(1050.0f, 890.0f);
	ControllableChar::ResetLife();
}
void Sophia::Update(DWORD dt, vector<GameObject*>* coObject)
{
	ControllableChar::Update(dt, coObject);
	if (HealthPoint > 0)
	{
		timerRU += vtRU * dt;
		timerOH += vtOH * dt;
		if (IsFalling == false && (currentAni == 38 || currentAni == 39))
		{
			currentAni == 38 ? currentAni = lastAni = 0 : currentAni = lastAni = 1;
		}
		if (HasBeenUp == 1)
		{
			if (currentAni > 17 && currentAni < 26 && timerRU >= 60)
			{
				y += 12.0f;
				HasBeenUp = 0;

			}
		}

		if (IsUpReleased && ((currentAni > 17 && currentAni < 26) || (currentAni > 33 && currentAni < 36)))
		{
			if (timerRU > 60)
			{
				timerRU = 201;
				if (currentAni == 35 || currentAni == 34)
				{
					currentAni == 34 ? currentAni = 26 + lastFrame : currentAni = 30 + lastFrame;
					lastAni = currentAni;
				}
				designatedFrame = -1;
			}
			else
			{
				HasBeenUp = false;
				//IsUpBlocked = 0;
				currentAni = 0;
				//y -= 4.0f;
			}
			IsUpReleased = false;
			*status = NOTHING;
		}

		if (HasBeenUp == 0) vy -= Hoverlv;
	}
	//set cam pos
	if(FlagStopUpdate == false)
	{
		lastX = x;
		((lastY < y || lastY - 80.0f>y) && LockCam(lastX, lastY) == false) ? lastY = y : lastY = lastY;
		CGame::GetInstance()->SetCamPos(lastX - 150.0f, lastY + 150.0f);
	}
}

void Sophia::Render()
{
	//RenderBoundingBox();
	if (HealthPoint > 0)
	{
		bool Flip = false;
		if (currentAni >= 0 && designatedFrame == -1)
		{
			animations[currentAni]->Render(x, y, -1, true, false, RenderColor);
			if ((currentAni < 10 && currentAni>1) && animations[currentAni]->GetCurrentFrame() == 1)
			{
				if (currentAni > 5 && currentAni < 10) currentAni = lastAni = 1;
				else if (currentAni > 1 && currentAni < 6) currentAni = lastAni = 0;
				lastFrame = 1;
			}
			else if ((currentAni > 17 && currentAni < 26) && animations[currentAni]->GetCurrentFrame() == 1)
			{
				y += 1.0f;
				designatedFrame = 0;
			}
			else if (currentAni > 25 && currentAni < 34 && animations[currentAni]->GetCurrentFrame() == 2)
			{
				currentAni >= 30 ? currentAni = lastAni = 1 : currentAni = lastAni = 0;
				designatedFrame = 0;
				//IsUpBlocked = 2;
			}
		}
		else if (((currentAni < 3 && lastAni < 3) || (currentAni > 33 && currentAni < 36)) && designatedFrame != -1)
		{
			animations[lastAni]->Render(x, y, lastFrame, true, false, RenderColor);
			/*if (IsUpBlocked == 2) IsUpBlocked = 0;*/
		}
		else if ((currentAni > 17 && currentAni < 26) && designatedFrame != -1)
		{
			int tempFrame = 0;
			if (timerRU >= 60 && timerRU < 200)
			{
				tempFrame = 3;
				vtRU = 0;
			}
			else if (timerRU < 60 && timerRU>40) tempFrame = 2;
			else if (timerRU < 20) tempFrame = 1;
			else if (timerRU > 200)
			{
				currentAni = currentAni + 8;
				lastAni = currentAni;
				//y += 3.0f;
			}
			animations[currentAni]->Render(x, y, tempFrame, true, false, RenderColor);
		}
		if (IsJasonOut == true || (IsJasonOut == false && (currentAni == 36 || currentAni == 37)))
		{
			if (timerOH >= 0)
			{
				if (currentAni == 36)
				{
					Flip = false;
					animations[currentAni]->Render(x, y, 0, true, Flip, RenderColor);
				}
				else if (currentAni == 37)
				{
					Flip = true;
					animations[currentAni]->Render(x, y, 0, true, Flip, RenderColor);
				}
			}
			else
			{
				if (IsJasonOut == false)
				{
					y -= 6.5f;
					if (currentAni == 36) currentAni = lastAni = 0;
					else if (currentAni == 37) currentAni = lastAni = 1;
					IsJasonBack = true;
				}
				animations[currentAni]->Render(x, y, 1, true, Flip, RenderColor);
				vtOH = 0; timerOH = -1;
			}
		}
	}
	else
	{
		Sound::getInstance()->play("explode", false, 1);
		if(currentAni!=40)
		currentAni = lastAni = 40;
		//y += 20.0f;
		animations[currentAni]->Render(x, y, -1, true, false, 255);
		if (animations[currentAni]->GetCurrentFrame() == 1)
		{
			y += 1.0f;
			FlagDead = true;
			ResetLife();
		}
	}
}

void Sophia::SetAni(int ani)
{
	if (HealthPoint > 0)
	{
		lastFrame = animations[lastAni]->GetCurrentFrame();
		if (FlagAutomatic == true)
		{
			ani = -1;
			designatedFrame = -1;
		}
		else 	designatedFrame = 0;
		switch (ani)
		{
		case GO_RIGHT:
			ani = 0;
			if (*status == LOOKUP)
			{
				if (HasBeenUp == false) ani = 34;
				else
				{
					HasBeenUp = false;
					*status = NOTHING;
				}
			}
			else if (IsFalling == true)
			{
				ani = 38;
			}
			else if (ani != lastAni && *status == NOTHING)
			{
				ani = lastFrame + 2;
			}
			designatedFrame = -1;
			vx = 0.1f;
			break;
		case GO_LEFT:
			ani = 1;
			if (*status == LOOKUP)
			{
				if (HasBeenUp == false) ani = 35;
				else
				{
					HasBeenUp = false;
					*status = NOTHING;
				}
			}
			else if (IsFalling == true)
			{
				ani = 39;
			}
			else if (ani != lastAni && *status == NOTHING)
			{
				ani = lastFrame + 6;
			}
			designatedFrame = -1;
			vx = -0.1f;
			break;
		case GO_UP:
			if (*status != LOOKUP)
			{
				IsUpReleased = false;
				*status = LOOKUP;
				if (lastAni == 0) ani = lastFrame + 18; else ani = lastFrame + 22;
				designatedFrame = -1;
				timerRU = 0;
				vtRU = 0.5f;
				y += 7.0f;
				vy = 0;
				HasBeenUp = 1;
			}
			else ani = -1;
			break;
		case JUMP:
			if (IsFalling == false)
			{
				//vx = 0;
				if (*status == NOTHING)
				{
					if (lastAni == 0) ani = lastFrame + 10; else ani = lastFrame + 14;
					vy = +0.4f;
					designatedFrame = -1;
				}
				else if (*status == LOOKUP)
				{
					ani = lastAni;
					vy = +0.45f;
					designatedFrame = 0;
				}
				IsFalling = true;
			}
			else ani = -1;
			break;
		case FIRE:
			ani = lastAni;
			if (timerCD <= 0)
			{
				if (ani == 0) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x + 22.0f/*30.0f*/, y - 2.0f, 0.2f, 0.0f, true, 0);
				else if (ani == 1) WeaponType[curWeapon]->AddBullet(curWeapon, 0, x, y - 2.0f, -0.2f, 0.0f, false, 1);
				else if (ani == 34 || ani == 35
					|| ((ani > 17 && ani < 26) && designatedFrame != -1))
					WeaponType[curWeapon]->AddBullet(curWeapon, 1, x + 12.0f, y, 0.0f, 0.2f, false, 2);
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
		case GET_OUT:
			IsJasonOut = true;
			IsJasonBack = false;
			timerOH = 500.0f;
			vtOH = -0.5f;
			*status = NOTHING;
			if (lastAni == 0 || (lastAni > 17 && lastAni < 22) || lastAni == 34) ani = 36;
			else ani = 37;
			FlagStopUpdate = true;
			y += 8.5f;
			vx = 0; vy = 0;
			break;
		case GET_IN:
			IsJasonOut = false;
			timerOH = 300.0f;
			vtOH = -0.5f;
			FlagStopUpdate = false;
			y += 11.0f;
			if (lastAni == 37) ani = 37;
			else if (lastAni == 36) ani = 36;
			break;
		default:
			if (FlagAutomatic == false)
			{
				ani = -1;
				if (lastAni > 25 && lastAni < 34) designatedFrame = -1;
				if (IsFalling == true) {
					if (lastAni == 0)
					{
						ani = lastFrame + 10;
						designatedFrame = -1;
					}
					else if (lastAni == 1)
					{
						ani = lastFrame + 14;
						designatedFrame = -1;
					}
					else if ((lastAni > 33 && lastAni < 36) || lastAni == 38 || lastAni == 39)
					{
						designatedFrame = -1;
					}
				}
				else vx = 0;
			}
			/*if(*status==LOOKUP)*/ //y += 0.5f;
		}
		if (ani != lastAni && ani >= 0)
		{
			if ((ani > 5 && ani < 10) || (ani > 9 && ani < 14)) {
				lastAni = 0;
			}
			else if ((ani > 1 && ani < 6) || (ani > 13 && ani < 18))
			{
				lastAni = 1;
			}
			if (ani < 1 || ani>17) this->lastAni = ani;
		}
		if (ani < 0) ani = lastAni;
		MovingObject::SetAni(ani);
	}
}