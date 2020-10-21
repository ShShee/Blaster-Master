#include "ControllableChar.h"

MainPlayer* MainPlayer::_instance = NULL;

MainPlayer::MainPlayer()
{
	ControllableChar* addplayer;

	addplayer = new Sophia();
	Player.push_back(addplayer);

	addplayer = new Jason();
	Player.push_back(addplayer);

	addplayer = new JasonOW();
	Player.push_back(addplayer);
}

void MainPlayer::LoadTexture()
{
	CTextures::GetInstance()->Add(ID_TEX_SOPHIA, L"SpritesSource\\Sophia.png", D3DCOLOR_XRGB(54, 115, 1));
	CTextures::GetInstance()->Add(ID_TEX_JASON, L"SpritesSource\\Jason.png", D3DCOLOR_XRGB(54, 115, 1));

	texSophia = CTextures::GetInstance()->Get(ID_TEX_SOPHIA);
	texJason = CTextures::GetInstance()->Get(ID_TEX_JASON);

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	//Sophia

	//to left
	sprites->Add(10, 146, 5, 172, 23, texSophia);//1
	sprites->Add(11, 178, 5, 204, 23, texSophia);//3
	sprites->Add(12, 211, 5, 237, 23, texSophia);//5
	sprites->Add(13, 242, 5, 268, 23, texSophia);//7
	ani = new CAnimation(100);
	for (int i = 10; i < 14; i++) ani->Add(i);
	animations->Add(1, ani);

	//to right
	sprites->Add(18, 13, 5, 39, 23, texSophia);//1
	sprites->Add(21, 44, 5, 70, 23, texSophia);//3
	sprites->Add(20, 77, 5, 103, 23, texSophia);//5
	sprites->Add(19, 109, 5, 135, 23, texSophia);//7
	ani = new CAnimation(100);
	for (int i = 18; i < 22; i++) ani->Add(i);
	animations->Add(2, ani);

	//turn to right
	sprites->Add(26, 146, 80, 170, 98, texSophia);//18

	sprites->Add(27, 179, 80, 203, 98, texSophia);//20

	sprites->Add(28, 211, 80, 235, 98, texSophia);//22

	sprites->Add(29, 244, 80, 268, 98, texSophia);//24

	for (int i = 26, j = 18, id = 3; i < 30; i++, j += 2, id++)
	{
		ani = new CAnimation(300);
		ani->Add(i);
		ani->Add(j);
		animations->Add(id, ani);
	}

	//turn to left
	sprites->Add(30, 12, 80, 36, 98, texSophia);//10

	sprites->Add(31, 45, 80, 69, 98, texSophia);//12

	sprites->Add(32, 77, 80, 101, 98, texSophia);//14

	sprites->Add(33, 111, 80, 135, 98, texSophia);//16

	for (int i = 30, j = 10, id = 7; i < 34; i++, j += 2, id++)
	{
		ani = new CAnimation(300);
		ani->Add(i);
		ani->Add(j);
		animations->Add(id, ani);
	}

	//jump left
	sprites->Add(34, 146, 130, 172, 151, texSophia);//10

	sprites->Add(35, 178, 130, 204, 151, texSophia);//12

	sprites->Add(36, 211, 130, 237, 151, texSophia);//14

	sprites->Add(37, 245, 130, 271, 151, texSophia);//16

	for (int i = 34, j = 10, id = 11; i < 38; i++, j += 2, id++)
	{
		ani = new CAnimation(600);
		ani->Add(i);
		ani->Add(j);
		animations->Add(id, ani);
	}
	
	//jump right
	sprites->Add(38, 10, 130, 36, 151, texSophia);//18

	sprites->Add(39, 44, 130, 70, 151, texSophia);//20

	sprites->Add(40, 77, 130, 103, 151, texSophia);//22

	sprites->Add(41, 109, 130, 135, 151, texSophia);//24

	for (int i = 38, j = 18, id = 15; i < 42; i++, j += 2, id++)
	{
		ani = new CAnimation(600);
		ani->Add(i);
		ani->Add(j);
		animations->Add(id, ani);
	}

	//look up left
	sprites->Add(42, 146, 187, 171, 213, texSophia);
	sprites->Add(43, 146, 218, 171, 246, texSophia);
	sprites->Add(44, 146, 250, 171, 280, texSophia);
	sprites->Add(45, 146, 283, 172, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 42; i < 46; i++) ani->Add(i);
	animations->Add(19, ani);

	sprites->Add(46, 176, 187, 171, 213, texSophia);
	sprites->Add(47, 176, 218, 171, 246, texSophia);
	sprites->Add(48, 176, 250, 171, 280, texSophia);
	sprites->Add(49, 176, 283, 172, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 46; i < 50; i++) ani->Add(i);
	animations->Add(20, ani);

	sprites->Add(50, 209, 187, 171, 213, texSophia);
	sprites->Add(51, 209, 218, 171, 246, texSophia);
	sprites->Add(52, 209, 250, 171, 280, texSophia);
	sprites->Add(53, 209, 283, 172, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 50; i < 54; i++) ani->Add(i);
	animations->Add(21, ani);

	sprites->Add(54, 243, 187, 171, 213, texSophia);
	sprites->Add(55, 243, 218, 171, 246, texSophia);
	sprites->Add(56, 243, 250, 171, 280, texSophia);
	sprites->Add(57, 243, 283, 172, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 54; i < 58; i++) ani->Add(i);
	animations->Add(22, ani);

	//look up right
	sprites->Add(58, 13, 187, 38, 213, texSophia);//18
	sprites->Add(59, 12, 218, 37, 246, texSophia);
	sprites->Add(60, 14, 250, 39, 280, texSophia);
	sprites->Add(61, 13, 283, 39, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 58; i < 62; i++) ani->Add(i);
	animations->Add(23, ani);

	sprites->Add(62, 47, 187, 72, 213, texSophia);//20
	sprites->Add(63, 47, 218, 72, 246, texSophia);
	sprites->Add(64, 49, 250, 74, 280, texSophia);
	sprites->Add(65, 48, 283, 74, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 62; i < 66; i++) ani->Add(i);
	animations->Add(24, ani);

	sprites->Add(66, 80, 187, 105, 213, texSophia);//22
	sprites->Add(67, 80, 218, 105, 246, texSophia);
	sprites->Add(68, 82, 250, 107, 280, texSophia);
	sprites->Add(69, 79, 283, 105, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 66; i < 70; i++) ani->Add(i);
	animations->Add(25, ani);

	sprites->Add(70, 110, 187, 135, 213, texSophia);//24
	sprites->Add(71, 110, 218, 135, 246, texSophia);
	sprites->Add(72, 110, 250, 135, 280, texSophia);
	sprites->Add(73, 109, 283, 135, 317, texSophia);
	ani = new CAnimation(600);
	for (int i = 70; i < 74; i++) ani->Add(i);
	animations->Add(26, ani);

	for (int i = 1; i < 27; i++) Player[0]->Add_Image(i);

	//Jason

	//standing
	sprites->Add(101, 3, 30, 11, 46, texJason);
	sprites->Add(102, 30, 31, 38, 46, texJason);
	sprites->Add(103, 21, 30, 29, 46, texJason);
	sprites->Add(104, 12, 31, 20, 46, texJason);

	//lying
	sprites->Add(105, 3, 47, 18, 54, texJason);
	sprites->Add(106, 21, 47, 36, 54, texJason);

	//idle
	ani = new CAnimation(300);
	ani->Add(101);
	animations->Add(50, ani);

	//walking
	ani = new CAnimation(300);
	ani->Add(102);
	ani->Add(103);
	ani->Add(104);
	animations->Add(51, ani);

	//lying
	ani = new CAnimation(300);
	ani->Add(105);
	ani->Add(106);
	animations->Add(52, ani);

	for (int i = 50; i < 53; i++)
	{
		Player[1]->Add_Image(i);
		Player[1]->Add_Image(i);
	}

	//JasonOW

	//left - right
	sprites->Add(1001, 233, 69, 257, 101, texJason);
	sprites->Add(1002, 258, 69, 282, 101, texJason);
	sprites->Add(1003, 208, 69, 232, 101, texJason);
	
	//up
	sprites->Add(1004, 233, 36, 257, 68, texJason);
	sprites->Add(1005, 258, 36, 282, 68, texJason);
	sprites->Add(1006, 208, 36, 232, 68, texJason);

	//down
	sprites->Add(1007, 233, 3, 257, 35, texJason);
	sprites->Add(1008, 258, 3, 282, 35, texJason);
	sprites->Add(1009, 208, 3, 232, 35, texJason);

	//left-right
	ani = new CAnimation(100);
	ani->Add(1001);
	ani->Add(1002);
	ani->Add(1003);
	animations->Add(100, ani);

	//up
	ani = new CAnimation(100);
	ani->Add(1004);
	ani->Add(1005);
	ani->Add(1006);
	animations->Add(101, ani);

	//down
	ani = new CAnimation(100);
	ani->Add(1007);
	ani->Add(1008);
	ani->Add(1009);
	animations->Add(102, ani);

	Player[2]->Add_Image(100);
	Player[2]->Add_Image(100);
	Player[2]->Add_Image(101);
	Player[2]->Add_Image(102);
}

void MainPlayer::Update(DWORD dt)
{
	Player[curPlayer]->Update(dt);
}

void MainPlayer::Render()
{
	Player[curPlayer]->Render();
}

void MainPlayer::SetAni(int ani)
{
	Player[curPlayer]->SetAni(ani);
}

MainPlayer* MainPlayer::GetInstance()
{
	if (_instance == NULL) _instance = new MainPlayer();
	return _instance;
}

void Sophia::Update(DWORD dt)
{
	MovingObject::Update(dt);
}

void Sophia::Render()
{
	if (currentAni >= 0 && designatedFrame == -1)
	{
		//if (*state != GO_LEFT) flipX = false;
		animations[currentAni]->Render(x, y, -1, true);
	}
	else
	{
		//if (lastAni==1) flipX = false;
		/*if (lastAni == 0 && *laststate == GO_LEFT) flipX = true;*/
		animations[lastAni]->Render(x, y, lastFrame, true);
	}
}

void Sophia::SetAni(int ani)
{
	designatedFrame = 0;
	switch (ani)
	{
	case GO_RIGHT:
		//if (*status == LYING) ani = 4; else ani = 2;
		vx = 0.02f;
		lastFrame = animations[lastAni]->GetCurrentFrame() ;
		designatedFrame = -1;
		break;
	case GO_LEFT:
		//if (*status == LYING) ani = 5; else ani = 3;
		vx = -0.02f;
		lastFrame = animations[lastAni]->GetCurrentFrame();
		designatedFrame = -1;
		break;
	/*case GO_UP:
		if (*status == LYING)
		{
			*status = NOTHING;
			if (lastAni == 4) ani = 0; else ani = 1;
		}
		else ani = -1;
		break;
	case GO_DOWN:
		if (*status == NOTHING)
		{
			*status = LYING;
			if (lastAni == 0) ani = 4; else ani = 5;
		}
		else ani = -1;
		break;
	case JUMP:
		if (*status == NOTHING)
		{
			*status = JUMPING;
			vx = 0; vy = +0.2f;
			designatedFrame = 2;
			if (lastAni % 2 == 0) ani = 2; else ani = 3;
		}
		else ani = -1;
		break;*/
	case IDLE:
		vx = 0;
		/*if(*status!=JUMPING) vy = 0;*/
		//if (*status == JUMPING) designatedFrame = 2;
		//if (lastAni == 2 && *status == NOTHING) ani = 0;
		//else if (lastAni == 3 && *status == NOTHING) ani = 1;
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

void Jason::Update(DWORD dt)
{
	MovingObject::Update(dt);
	vy -= 0.03f;
	if (y <= 100)
	{
		vy = 0; y = 100.0f;
		if (*status == JUMPING) *status = NOTHING;
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
	if (currentAni % 2 == 0 || lastAni % 2 == 0) flipX = true;
	if (currentAni >= 0 && designatedFrame == -1)
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
		if (*status == LYING)
		{
			*status = NOTHING;
			if (lastAni == 4) ani = 0; else ani = 1;
		}
		else ani = -1;
		break;
	case GO_DOWN:
		if (*status == NOTHING)
		{
			*status = LYING;
			if (lastAni == 0) ani = 4; else ani = 5;
		}
		else ani = -1;
		break;
	case JUMP:
		if (*status == NOTHING)
		{
			*status = JUMPING;
			vx = 0; vy = +0.2f;
			designatedFrame = 2;
			if (lastAni % 2 == 0) ani = 2; else ani = 3;
		}
		else ani = -1;
		break;
	case IDLE:
		vx = 0;
		/*if(*status!=JUMPING) vy = 0;*/
		if (*status == JUMPING) designatedFrame = 2;
		if (lastAni == 2 && *status == NOTHING) ani = 0;
		else if (lastAni == 3 && *status == NOTHING) ani = 1;
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
	bool flipX = false;
	if (currentAni == 0 || lastAni == 0) flipX = true;
	if (currentAni >= 0)
	{
		//if (*state != GO_LEFT) flipX = false;
		animations[currentAni]->Render(x, y, -1, true, flipX);
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
	if (ani != lastAni && ani >= 0)
		//{
		//	animations[ani]->SetCurrentFrame(currentFrame+1);
		//}
		//else
	{
		this->lastAni = ani;
		//this->currentFrame = animations[ani]->GetCurrentFrame();
	}
}
