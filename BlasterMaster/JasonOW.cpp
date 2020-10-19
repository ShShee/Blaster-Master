#include "JasonOW.h"

JasonOW* JasonOW::_instance = NULL;

void JasonOW::Update(DWORD dt)
{
	MovingObject::Update(dt);
	if (vx > 0 && x > 2084) x = 2084;
	else if (vx < 0 && x < 0) x = 0;
	if (vy > 0 && y > 2084) y = 2084;
	else if (vy < 0 && y < 0) y = 0;
}

void JasonOW::Render()
{
	bool flipX=false;
	if (currentAni==0 || lastAni==0) flipX = true;
	if (currentAni >= 0)
	{
		//if (*state != GO_LEFT) flipX = false;
		animations[currentAni]->Render(x, y,-1,true,flipX);
	}
	else {
		//if (lastAni==1) flipX = false;
		/*if (lastAni == 0 && *laststate == GO_LEFT) flipX = true;*/
		animations[lastAni]->Render(x, y, /*currentFrame*/0, true, flipX);
	}
}

void JasonOW::SetAni(int ani)
{
	MovingObject::SetAni(ani);
		switch (ani)
		{
		case GO_RIGHT:
			vx = 0.3f; vy = 0;
			break;
		case GO_LEFT:
			vx = -0.3f; vy = 0;
			break;
		case GO_UP:
			vy = +0.3f; vx = 0;
			break;
		case GO_DOWN:
			vx = 0.0f; vy = -0.3f;
			break;
		case IDLE:
			vx = 0; vy = 0;
			break;
		}
		if (ani!=lastAni && ani>=0)
		//{
		//	animations[ani]->SetCurrentFrame(currentFrame+1);
		//}
		//else
		{
			 this->lastAni = ani;
			//this->currentFrame = animations[ani]->GetCurrentFrame();
		}
}
JasonOW* JasonOW::GetInstance()
{
	if (_instance == NULL) _instance = new JasonOW();
	return _instance;
}
