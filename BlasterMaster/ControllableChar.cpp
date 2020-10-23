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
	sprites->Add(21, 109, 5, 135, 23, texSophia);//7
	sprites->Add(20, 77, 5, 103, 23, texSophia);//5
	sprites->Add(19, 44, 5, 70, 23, texSophia);//3
	sprites->Add(18, 13, 5, 39, 23, texSophia);//1

	ani = new CAnimation(100);
	for (int i = 18; i < 22; i++) ani->Add(i);
	animations->Add(2, ani);

	//turn to left
	sprites->Add(26, 146, 80, 170, 98, texSophia);//10
	sprites->Add(27, 179, 80, 203, 98, texSophia);//11
	sprites->Add(28, 211, 80, 235, 98, texSophia);//12
	sprites->Add(29, 244, 80, 268, 98, texSophia);//13

	ani = new CAnimation(10);
	ani->Add(26);
	ani->Add(18);
	animations->Add(3, ani);

	ani = new CAnimation(10);
	ani->Add(27);
	ani->Add(19);
	animations->Add(4, ani);

	ani = new CAnimation(10);
	ani->Add(28);
	ani->Add(20);
	animations->Add(5, ani);

	ani = new CAnimation(10);
	ani->Add(29);
	ani->Add(21);
	animations->Add(6, ani);
	//turn to right
	sprites->Add(33, 111, 80, 135, 98, texSophia);//16

	sprites->Add(32, 77, 80, 101, 98, texSophia);//14

	sprites->Add(31, 45, 80, 69, 98, texSophia);//12

	sprites->Add(30, 12, 80, 36, 98, texSophia);//10

	ani = new CAnimation(10);
	ani->Add(30);
	ani->Add(10);
	animations->Add(7, ani);

	ani = new CAnimation(10);
	ani->Add(31);
	ani->Add(11);
	animations->Add(8, ani);

	ani = new CAnimation(10);
	ani->Add(32);
	ani->Add(12);
	animations->Add(9, ani);

	ani = new CAnimation(10);
	ani->Add(33);
	ani->Add(13);
	animations->Add(10, ani);

	//jump left
	sprites->Add(34, 146, 130, 172, 151, texSophia);//10

	sprites->Add(35, 178, 130, 204, 151, texSophia);//12

	sprites->Add(36, 211, 130, 237, 151, texSophia);//14

	sprites->Add(37, 245, 130, 271, 151, texSophia);//16

	for (int i = 34, j = 10, id = 11; i < 38; i++, j ++, id++)
	{
		ani = new CAnimation(50);
		ani->Add(i);
		//ani->Add(j);
		animations->Add(id, ani);
	}
	
	//jump right
	sprites->Add(38, 10, 130, 36, 151, texSophia);//18

	sprites->Add(39, 44, 130, 70, 151, texSophia);//20

	sprites->Add(40, 77, 130, 103, 151, texSophia);//22

	sprites->Add(41, 109, 130, 135, 151, texSophia);//24

	for (int i = 38, j = 18, id = 15; i < 42; i++, j ++, id++)
	{
		ani = new CAnimation(50);
		ani->Add(i);
		//ani->Add(j);
		animations->Add(id, ani);
	}

	//look up left
	sprites->Add(42, 146, 187, 171, 213, texSophia);
	sprites->Add(43, 146, 218, 171, 246, texSophia);
	sprites->Add(44, 146, 250, 171, 280, texSophia);
	sprites->Add(45, 146, 283, 172, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 42; i < 46; i++) ani->Add(i);
	animations->Add(19, ani);

	sprites->Add(46, 176, 187, 201, 213, texSophia);
	sprites->Add(47, 176, 218, 201, 246, texSophia);
	sprites->Add(48, 176, 250, 199, 280, texSophia);
	sprites->Add(49, 176, 283, 202, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 46; i < 50; i++) ani->Add(i);
	animations->Add(20, ani);

	sprites->Add(50, 209, 187, 234, 213, texSophia);
	sprites->Add(51, 209, 218, 234, 246, texSophia);
	sprites->Add(52, 209, 250, 232, 280, texSophia);
	sprites->Add(53, 209, 283, 233, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 50; i < 54; i++) ani->Add(i);
	animations->Add(21, ani);

	sprites->Add(54, 243, 187, 268, 213, texSophia);
	sprites->Add(55, 243, 218, 269, 246, texSophia);
	sprites->Add(56, 243, 250, 267, 280, texSophia);
	sprites->Add(57, 243, 283, 268, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 54; i < 58; i++) ani->Add(i);
	animations->Add(22, ani);

	//look up right
	sprites->Add(58, 13, 187, 38, 213, texSophia);//18
	sprites->Add(59, 12, 218, 37, 246, texSophia);
	sprites->Add(60, 14, 250, 39, 280, texSophia);
	sprites->Add(61, 13, 283, 39, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 58; i < 62; i++) ani->Add(i);
	animations->Add(23, ani);

	sprites->Add(62, 47, 187, 72, 213, texSophia);//20
	sprites->Add(63, 47, 218, 72, 246, texSophia);
	sprites->Add(64, 49, 250, 74, 280, texSophia);
	sprites->Add(65, 48, 283, 74, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 62; i < 66; i++) ani->Add(i);
	animations->Add(24, ani);

	sprites->Add(66, 80, 187, 105, 213, texSophia);//22
	sprites->Add(67, 80, 218, 105, 246, texSophia);
	sprites->Add(68, 82, 250, 107, 280, texSophia);
	sprites->Add(69, 79, 283, 105, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 66; i < 70; i++) ani->Add(i);
	animations->Add(25, ani);

	sprites->Add(70, 110, 187, 135, 213, texSophia);//24
	sprites->Add(71, 110, 218, 135, 246, texSophia);
	sprites->Add(72, 110, 250, 135, 280, texSophia);
	sprites->Add(73, 109, 283, 135, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 70; i < 74; i++) ani->Add(i);
	animations->Add(26, ani);

	//look up back left
	sprites->Add(77, 146, 187, 171, 213, texSophia);
	sprites->Add(76, 146, 218, 171, 246, texSophia);
	sprites->Add(75, 146, 250, 171, 280, texSophia);
	sprites->Add(74, 146, 283, 172, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 74; i < 78; i++) ani->Add(i);
	animations->Add(27, ani);

	sprites->Add(81, 176, 187, 201, 213, texSophia);
	sprites->Add(80, 176, 218, 201, 246, texSophia);
	sprites->Add(79, 176, 250, 199, 280, texSophia);
	sprites->Add(78, 176, 283, 202, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 78; i < 82; i++) ani->Add(i);
	animations->Add(28, ani);

	sprites->Add(85, 209, 187, 234, 213, texSophia);
	sprites->Add(84, 209, 218, 234, 246, texSophia);
	sprites->Add(83, 209, 250, 232, 280, texSophia);
	sprites->Add(82, 209, 283, 233, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 82; i < 86; i++) ani->Add(i);
	animations->Add(29, ani);

	sprites->Add(89, 243, 187, 268, 213, texSophia);
	sprites->Add(88, 243, 218, 269, 246, texSophia);
	sprites->Add(87, 243, 250, 267, 280, texSophia);
	sprites->Add(86, 243, 283, 268, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 86; i < 90; i++) ani->Add(i);
	animations->Add(30, ani);

	//look up right
	sprites->Add(93, 13, 187, 38, 213, texSophia);//18
	sprites->Add(92, 12, 218, 37, 246, texSophia);
	sprites->Add(91, 14, 250, 39, 280, texSophia);
	sprites->Add(90, 13, 283, 39, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 90; i < 94; i++) ani->Add(i);
	animations->Add(31, ani);

	sprites->Add(97, 47, 187, 72, 213, texSophia);//20
	sprites->Add(96, 47, 218, 72, 246, texSophia);
	sprites->Add(95, 49, 250, 74, 280, texSophia);
	sprites->Add(94, 48, 283, 74, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 94; i < 98; i++) ani->Add(i);
	animations->Add(32, ani);

	sprites->Add(101, 80, 187, 105, 213, texSophia);//22
	sprites->Add(100, 80, 218, 105, 246, texSophia);
	sprites->Add(99, 82, 250, 107, 280, texSophia);
	sprites->Add(98, 79, 283, 105, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 98; i < 102; i++) ani->Add(i);
	animations->Add(33, ani);

	sprites->Add(105, 110, 187, 135, 213, texSophia);//24
	sprites->Add(104, 110, 218, 135, 246, texSophia);
	sprites->Add(103, 110, 250, 135, 280, texSophia);
	sprites->Add(102, 109, 283, 135, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 102; i < 106; i++) ani->Add(i);
	animations->Add(34, ani);

	//look up walk left
	sprites->Add(106, 146, 283, 172, 317, texSophia);
	sprites->Add(107, 176, 283, 202, 317, texSophia);
	sprites->Add(108, 209, 283, 233, 317, texSophia);
	sprites->Add(109, 243, 283, 268, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 106; i < 110; i++) ani->Add(i);
	animations->Add(35, ani);

	//look up walk right
	sprites->Add(110, 13, 283, 39, 317, texSophia);
	sprites->Add(111, 48, 283, 74, 317, texSophia);
	sprites->Add(112, 79, 283, 105, 317, texSophia);
	sprites->Add(113, 109, 283, 135, 317, texSophia);
	ani = new CAnimation(30);
	for (int i = 110; i < 114; i++) ani->Add(i);
	animations->Add(36, ani);

	for (int i = 1; i < 37; i++) Player[0]->Add_Image(i);

	//Jason

	//standing
	sprites->Add(1001, 3, 30, 11, 46, texJason);
	sprites->Add(1002, 30, 31, 38, 46, texJason);
	sprites->Add(1003, 21, 30, 29, 46, texJason);
	sprites->Add(1004, 12, 31, 20, 46, texJason);

	//lying
	sprites->Add(1005, 3, 47, 18, 54, texJason);
	sprites->Add(1006, 21, 47, 36, 54, texJason);

	//idle
	ani = new CAnimation(300);
	ani->Add(1001);
	animations->Add(500, ani);

	//walking
	ani = new CAnimation(300);
	ani->Add(1002);
	ani->Add(1003);
	ani->Add(1004);
	animations->Add(501, ani);

	//lying
	ani = new CAnimation(300);
	ani->Add(1005);
	ani->Add(1006);
	animations->Add(502, ani);

	for (int i = 500; i < 503; i++)
	{
		Player[1]->Add_Image(i);
		Player[1]->Add_Image(i);
	}

	//JasonOW

	//left - right
	sprites->Add(10001, 233, 69, 257, 101, texJason);
	sprites->Add(10002, 258, 69, 282, 101, texJason);
	sprites->Add(10003, 208, 69, 232, 101, texJason);
	
	//up
	sprites->Add(10004, 233, 36, 257, 68, texJason);
	sprites->Add(10005, 258, 36, 282, 68, texJason);
	sprites->Add(10006, 208, 36, 232, 68, texJason);

	//down
	sprites->Add(10007, 233, 3, 257, 35, texJason);
	sprites->Add(10008, 258, 3, 282, 35, texJason);
	sprites->Add(10009, 208, 3, 232, 35, texJason);

	//left-right
	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(1000, ani);

	//up
	ani = new CAnimation(100);
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	animations->Add(1001, ani);

	//down
	ani = new CAnimation(100);
	ani->Add(10007);
	ani->Add(10008);
	ani->Add(10009);
	animations->Add(1002, ani);

	Player[2]->Add_Image(1000);
	Player[2]->Add_Image(1000);
	Player[2]->Add_Image(1001);
	Player[2]->Add_Image(1002);
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
	vy -= 0.03f;
	if (y < 100.0f)
	{
		vy = 0; y = 100.0f;
		if (*status == JUMPING) *status = NOTHING;
	}
}

void Sophia::Render()
{
	if (currentAni >= 0 && designatedFrame == -1)
	{
		animations[currentAni]->Render(x, y, -1, true);
		if ((currentAni < 10 && currentAni>1) && animations[currentAni]->GetCurrentFrame() == 1)
		{
			if (currentAni > 5 && currentAni < 10) currentAni = lastAni = 1;
			else if (currentAni > 1 && currentAni < 6) currentAni = lastAni = 0;
			lastFrame = 1;
			/*animations[currentAni]->Render(x, y, lastFrame, true);*/
		}
		else if ((currentAni > 17 && currentAni < 26) && animations[currentAni]->GetCurrentFrame() == 3)
		{
			//lastFrame = 3;
			designatedFrame = 0;
		}
	}
		if ((currentAni < 3 && lastAni < 3) && designatedFrame != -1)
		{
			animations[lastAni]->Render(x, y, lastFrame, true);
			/*if (*status == TURNAR) { if (lastAni == 0) lastAni = 1; else lastAni = 0; *status = NOTHING; }*/
		}
		if (IsUpReleased && (currentAni > 17 && currentAni < 26))
		{
			if (currentAni > 21 && currentAni<26) currentAni =lastAni= 1; else currentAni =lastAni= 0;
			animations[currentAni]->Render(x, y, lastFrame, true);
			*status = NOTHING;
			//IsUpReleased = false;
		}
		else if ((currentAni > 17 && currentAni < 26) && designatedFrame!=-1)
		{
			animations[currentAni]->Render(x, y, 3, true);
		}

}

void Sophia::SetAni(int ani)
{
	designatedFrame = 0;
	lastFrame = animations[lastAni]->GetCurrentFrame();
	switch (ani)
	{
	case GO_RIGHT:	
		if (*status == LOOKUP /*&& ani == lastAni*/)
		{
			ani = 34;
			designatedFrame = -1;
		}
		if (ani != lastAni && *status == NOTHING) 
		{
			ani = lastFrame + 2;
			designatedFrame = -1;
		}
		vx = 0.02f;

		break;
	case GO_LEFT:
		if (*status == LOOKUP && ani == lastAni)
		{
			ani = 35;
			designatedFrame = 0;
		}
		if (ani != lastAni && *status == NOTHING)
		{
			ani = lastFrame + 6;
			designatedFrame = -1;
		}
		vx = -0.02f;

		break;
	case GO_UP:
		if (*status !=JUMP/* && IsUpReleased*/)
		{
			IsUpReleased = false;
			if (lastAni == 0) ani = lastFrame+18; else ani = lastFrame+22;
			*status = LOOKUP;
			designatedFrame = -1;
		}
		//if (*status == LOOKUP)
		//{
		//	ani = lastAni;
		//	designatedFrame = 3;
		//}
		break;
	case JUMP:
		if (*status != JUMPING)
		{
			vx = 0; vy = +0.7f;
			if (*status == NOTHING)
			{
				if (lastAni ==0) ani = lastFrame + 10; else ani = lastFrame + 14;
				*status = JUMPING;
			}
			else if (*status == LOOKUP)
			{

			}	
			designatedFrame = -1;
		}
		else ani = -1;
		break;
	case IDLE:
		vx = 0;
		if (*status == JUMPING) {
			if (lastAni == 0) ani = lastFrame + 10; else ani = lastFrame + 14;
			designatedFrame = -1;
		}
		//if (IsUpReleased==true)
		//{
		//	*status = NOTHING;
		//	/*if (lastAni > 21 && lastAni<26) ani = 0; else */ani = 1;
		//	IsUpReleased = false;
		//}
		/*if(*status!=JUMPING) vy = 0;*/
		//if (*status == JUMPING) designatedFrame = 2;
		//if (lastAni == 2 && *status == NOTHING) ani = 0;
		//else if (lastAni == 3 && *status == NOTHING) ani = 1;

		break;
	}
	if (ani != lastAni && ani >= 0)
	{
		if ((ani > 5 && ani < 10)||(ani>9 && ani<14)/*||(ani>17 && ani<22)*/) {
			lastAni = 0;
		}
		else if ((ani > 1 && ani < 6) || (ani > 13 && ani < 18)/*||(ani>21 && ani<26)*/)
		{
			lastAni = 1;
		}
		if(ani<1 || ani>17) this->lastAni = ani;
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
