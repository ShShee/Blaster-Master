#include "Jason.h"

Jason* Jason::_instance = NULL;

void Jason::Update(DWORD dt)
{
	MovingObject::Update(dt);
	vy -= 0.03f;
	if (y <= 100)
	{
		vy = 0; y = 100.0f; 
		if(*status==JUMPING) *status = NOTHING;
	}
	//if (vx > 0 && x > 290) x = 290;
	//else 
	//if (vx < 0 && y < 0) y = 0;
	//if (vy > 0 && y > 290) y = 290;
	//else if (vy < 0 && y < 0) y = 0;
}

void Jason::Render()
{
	bool flipX = false;
	if (currentAni %2==0 || lastAni%2==0) flipX = true;
	if (currentAni >= 0 && designatedFrame ==-1)
	{
		//if (*state != GO_LEFT) flipX = false;
		animations[currentAni]->Render(x, y, -1, true, flipX);
	}
	else
	{
		//if (lastAni==1) flipX = false;
		/*if (lastAni == 0 && *laststate == GO_LEFT) flipX = true;*/
		animations[lastAni]->Render(x, y, designatedFrame, true, flipX);
	}
}

void Jason::SetAni(int ani)
{
	designatedFrame = 0;
	switch (ani)
	{
	case GO_RIGHT:
			if (*status == LYING) ani = 4; else ani = 2;
			vx = 0.3f;
			designatedFrame = -1;
			break;
	case GO_LEFT:
			if (*status == LYING) ani = 5; else ani = 3;
			vx = -0.3f;
			designatedFrame = -1;
		    break;
	case GO_UP:
		if (*status==LYING)
		{
			*status = NOTHING;
			if (lastAni == 4) ani = 0; else ani = 1;
		}
		else ani = -1;
		break;
	case GO_DOWN:
		if (*status==NOTHING)
		{
			*status = LYING;
			if (lastAni == 0) ani = 4; else ani = 5;
		}
		else ani = -1;
		break;
	case JUMP:
		if (*status ==NOTHING)
		{
			*status = JUMPING;
			vx = 0; vy = +0.2f;
			designatedFrame = 2;
			if (lastAni %2== 0) ani = 2; else ani = 3;
		}
		else ani = -1;
		break;
	case IDLE:
		vx = 0;
		/*if(*status!=JUMPING) vy = 0;*/
		if(*status==JUMPING) designatedFrame = 2;
		if (lastAni == 2 && *status==NOTHING) ani = 0;
		else if (lastAni == 3 && *status==NOTHING) ani = 1;
		break;
	}
	if (ani != lastAni && ani >= 0)
		//{
		//	animations[ani]->SetCurrentFrame(currentFrame+1);
		//}
		//else
	{
		this->lastAni = ani;
		//this->currentFrame = animations[ani]->GetCurrentFrame();
	}
	if (ani < 0) ani = lastAni;
	MovingObject::SetAni(ani);
}

Jason* Jason::GetInstance()
{
	if (_instance == NULL) _instance = new Jason();
	return _instance;
}
