#include "MainPlayer.h"

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

	CTextures::GetInstance()->Add(ID_TEX_HEALTHBAR, L"SpritesSource\\HealthBar.png", D3DCOLOR_XRGB(54, 115, 1));

	texSophia = CTextures::GetInstance()->Get(ID_TEX_SOPHIA);
	texJason = CTextures::GetInstance()->Get(ID_TEX_JASON);

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	#pragma region Sophia

	//to left
	sprites->Add(10, 146, 5, 172, 23, texSophia);//1
	sprites->Add(11, 178, 5, 204, 23, texSophia);//3
	sprites->Add(12, 211, 5, 237, 23, texSophia);//5
	sprites->Add(13, 242, 5, 268, 23, texSophia);//7

	ani = new CAnimation(50);
	for (int i = 10; i < 14; i++) ani->Add(i);
	animations->Add(1, ani);

	//to right
	sprites->Add(21, 109, 5, 135, 23, texSophia);//7
	sprites->Add(20, 77, 5, 103, 23, texSophia);//5
	sprites->Add(19, 44, 5, 70, 23, texSophia);//3
	sprites->Add(18, 13, 5, 39, 23, texSophia);//1

	ani = new CAnimation(50);
	for (int i = 18; i < 22; i++) ani->Add(i);
	animations->Add(2, ani);

	//turn to left
	sprites->Add(26, 146, 80, 170, 98, texSophia);//10
	sprites->Add(27, 179, 80, 203, 98, texSophia);//11
	sprites->Add(28, 211, 80, 235, 98, texSophia);//12
	sprites->Add(29, 244, 80, 268, 98, texSophia);//13

	ani = new CAnimation(100);
	ani->Add(26);
	ani->Add(18);
	animations->Add(3, ani);

	ani = new CAnimation(100);
	ani->Add(27);
	ani->Add(19);
	animations->Add(4, ani);

	ani = new CAnimation(100);
	ani->Add(28);
	ani->Add(20);
	animations->Add(5, ani);

	ani = new CAnimation(100);
	ani->Add(29);
	ani->Add(21);
	animations->Add(6, ani);
	//turn to right
	sprites->Add(33, 111, 80, 135, 98, texSophia);//16

	sprites->Add(32, 77, 80, 101, 98, texSophia);//14

	sprites->Add(31, 45, 80, 69, 98, texSophia);//12

	sprites->Add(30, 12, 80, 36, 98, texSophia);//10

	ani = new CAnimation(100);
	ani->Add(30);
	ani->Add(10);
	animations->Add(7, ani);

	ani = new CAnimation(100);
	ani->Add(31);
	ani->Add(11);
	animations->Add(8, ani);

	ani = new CAnimation(100);
	ani->Add(32);
	ani->Add(12);
	animations->Add(9, ani);

	ani = new CAnimation(100);
	ani->Add(33);
	ani->Add(13);
	animations->Add(10, ani);

	//jump left
	sprites->Add(34, 146, 130, 172, 151, texSophia);//10

	sprites->Add(35, 178, 130, 204, 151, texSophia);//12

	sprites->Add(36, 211, 130, 237, 151, texSophia);//14

	sprites->Add(37, 245, 130, 271, 151, texSophia);//16

	for (int i = 34, j = 10, id = 11; i < 38; i++, j++, id++)
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

	for (int i = 38, j = 18, id = 15; i < 42; i++, j++, id++)
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
	ani = new CAnimation(500);
	for (int i = 42; i < 46; i++) ani->Add(i);
	animations->Add(19, ani);

	sprites->Add(46, 176, 187, 201, 213, texSophia);
	sprites->Add(47, 176, 218, 201, 246, texSophia);
	sprites->Add(48, 176, 250, 199, 280, texSophia);
	sprites->Add(49, 176, 283, 202, 317, texSophia);
	ani = new CAnimation(500);
	for (int i = 46; i < 50; i++) ani->Add(i);
	animations->Add(20, ani);

	sprites->Add(50, 209, 187, 234, 213, texSophia);
	sprites->Add(51, 209, 218, 234, 246, texSophia);
	sprites->Add(52, 209, 250, 232, 280, texSophia);
	sprites->Add(53, 207, 283, 233, 317, texSophia);
	ani = new CAnimation(500);
	for (int i = 50; i < 54; i++) ani->Add(i);
	animations->Add(21, ani);

	sprites->Add(54, 243, 187, 268, 213, texSophia);
	sprites->Add(55, 243, 218, 269, 246, texSophia);
	sprites->Add(56, 243, 250, 267, 280, texSophia);
	sprites->Add(57, 242, 283, 268, 317, texSophia);
	ani = new CAnimation(500);
	for (int i = 54; i < 58; i++) ani->Add(i);
	animations->Add(22, ani);

	//look up right
	sprites->Add(58, 13, 187, 38, 213, texSophia);//18
	sprites->Add(59, 12, 218, 37, 246, texSophia);
	sprites->Add(60, 14, 250, 39, 280, texSophia);
	sprites->Add(61, 13, 283, 39, 317, texSophia);
	ani = new CAnimation(500);
	for (int i = 58; i < 62; i++) ani->Add(i);
	animations->Add(23, ani);

	sprites->Add(62, 47, 187, 72, 213, texSophia);//20
	sprites->Add(63, 47, 218, 72, 246, texSophia);
	sprites->Add(64, 49, 250, 74, 280, texSophia);
	sprites->Add(65, 48, 283, 74, 317, texSophia);
	ani = new CAnimation(500);
	for (int i = 62; i < 66; i++) ani->Add(i);
	animations->Add(24, ani);

	sprites->Add(66, 80, 187, 105, 213, texSophia);//22
	sprites->Add(67, 80, 218, 105, 246, texSophia);
	sprites->Add(68, 82, 250, 107, 280, texSophia);
	sprites->Add(69, 79, 283, 105, 317, texSophia);
	ani = new CAnimation(500);
	for (int i = 66; i < 70; i++) ani->Add(i);
	animations->Add(25, ani);

	sprites->Add(70, 110, 187, 135, 213, texSophia);//24
	sprites->Add(71, 110, 218, 135, 246, texSophia);
	sprites->Add(72, 110, 250, 135, 280, texSophia);
	sprites->Add(73, 109, 283, 135, 317, texSophia);
	ani = new CAnimation(500);
	for (int i = 70; i < 74; i++) ani->Add(i);
	animations->Add(26, ani);

	//look up back left
	sprites->Add(77, 146, 187, 171, 213, texSophia);
	sprites->Add(76, 146, 218, 171, 246, texSophia);
	sprites->Add(75, 146, 250, 171, 280, texSophia);
	//sprites->Add(74, 146, 283, 172, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 75; i < 78; i++) ani->Add(i);
	animations->Add(27, ani);

	sprites->Add(81, 176, 187, 201, 213, texSophia);
	sprites->Add(80, 176, 218, 201, 246, texSophia);
	sprites->Add(79, 176, 250, 199, 280, texSophia);
	//sprites->Add(78, 176, 283, 202, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 79; i < 82; i++) ani->Add(i);
	animations->Add(28, ani);

	sprites->Add(85, 209, 187, 234, 213, texSophia);
	sprites->Add(84, 209, 218, 234, 246, texSophia);
	sprites->Add(83, 209, 250, 232, 280, texSophia);
	//sprites->Add(82, 207, 283, 233, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 83; i < 86; i++) ani->Add(i);
	animations->Add(29, ani);

	sprites->Add(89, 243, 187, 268, 213, texSophia);
	sprites->Add(88, 243, 218, 269, 246, texSophia);
	sprites->Add(87, 243, 250, 267, 280, texSophia);
	//sprites->Add(86, 242, 283, 268, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 87; i < 90; i++) ani->Add(i);
	animations->Add(30, ani);

	//look up back right
	sprites->Add(93, 13, 187, 38, 213, texSophia);//18
	sprites->Add(92, 12, 218, 37, 246, texSophia);
	sprites->Add(91, 14, 250, 39, 280, texSophia);
	//sprites->Add(90, 13, 283, 39, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 91; i < 94; i++) ani->Add(i);
	animations->Add(31, ani);

	sprites->Add(97, 47, 187, 72, 213, texSophia);//20
	sprites->Add(96, 47, 218, 72, 246, texSophia);
	sprites->Add(95, 49, 250, 74, 280, texSophia);
	//sprites->Add(94, 48, 283, 74, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 95; i < 98; i++) ani->Add(i);
	animations->Add(32, ani);

	sprites->Add(101, 80, 187, 105, 213, texSophia);//22
	sprites->Add(100, 80, 218, 105, 246, texSophia);
	sprites->Add(99, 82, 250, 107, 280, texSophia);
	//sprites->Add(98, 79, 283, 105, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 99; i < 102; i++) ani->Add(i);
	animations->Add(33, ani);

	sprites->Add(105, 110, 187, 135, 213, texSophia);//24
	sprites->Add(104, 110, 218, 135, 246, texSophia);
	sprites->Add(103, 110, 250, 135, 280, texSophia);
	//sprites->Add(102, 109, 283, 135, 317, texSophia);
	ani = new CAnimation(20);
	for (int i = 103; i < 106; i++) ani->Add(i);
	animations->Add(34, ani);

	//look up walk left
	sprites->Add(106, 146, 283, 172, 317, texSophia);
	sprites->Add(107, 176, 283, 202, 317, texSophia);
	sprites->Add(108, 207, 283, 233, 317, texSophia);
	sprites->Add(109, 242, 283, 268, 317, texSophia);
	ani = new CAnimation(50);
	for (int i = 106; i < 110; i++) ani->Add(i);
	animations->Add(35, ani);

	//look up walk right
	sprites->Add(110, 13, 283, 39, 317, texSophia);
	sprites->Add(111, 48, 283, 74, 317, texSophia);
	sprites->Add(112, 79, 283, 105, 317, texSophia);
	sprites->Add(113, 109, 283, 135, 317, texSophia);
	ani = new CAnimation(50);
	for (int i = 110; i < 114; i++) ani->Add(i);
	animations->Add(36, ani);

	//get out
	sprites->Add(114, 105, 334, 131, 360, texSophia);
	ani = new CAnimation(1000);
	ani->Add(114);
	ani->Add(13);
	animations->Add(37, ani);

	ani = new CAnimation(1000);
	ani->Add(114);
	ani->Add(21);
	animations->Add(38, ani);

	//jump to right
	sprites->Add(115, 146, 130, 172, 151, texSophia);
	sprites->Add(116, 178, 130, 204, 151, texSophia);
	sprites->Add(117, 211, 130, 237, 151, texSophia);
	sprites->Add(118, 245, 130, 271, 151, texSophia);
	ani = new CAnimation(20);
	for (int i = 115; i < 119; i++) ani->Add(i);
	animations->Add(39, ani);

	//jump to left
	sprites->Add(119, 10, 130, 36, 151, texSophia);
	sprites->Add(120, 44, 130, 70, 151, texSophia);
	sprites->Add(121, 77, 130, 103, 151, texSophia);
	sprites->Add(122, 109, 130, 135, 151, texSophia);
	ani = new CAnimation(20);
	for (int i = 119; i < 123; i++) ani->Add(i);
	animations->Add(40, ani);


	sprites->Add(123, 159, 3, 204, 43, texJason);
	sprites->Add(124, 143, 45, 207, 92, texJason);
	ani = new CAnimation(500);
	ani->Add(123);
	ani->Add(124);
	animations->Add(41, ani);

	for (int i = 1; i < 42; i++) Player[0]->Add_Image(i);

	sprites->Add(500, 91, 21, 113, 27, texJason);
	ani = new CAnimation(100);
	ani->Add(500);
	animations->Add(250, ani);

	sprites->Add(501, 117, 20, 123, 42, texJason);
	ani = new CAnimation(100);
	ani->Add(501);
	animations->Add(251, ani);

	//for (int i = 250; i < 252; i++) Player[0]->Add_BulletImage(i, 0);

	sprites->Add(502, 73, 30, 80, 35, texJason);
	ani = new CAnimation(100);
	ani->Add(502);
	animations->Add(252, ani);

	sprites->Add(503, 92, 29, 97, 36, texJason);
	ani = new CAnimation(100);
	ani->Add(503);
	animations->Add(253, ani);

	for (int i = 250; i < 252; i++) Player[0]->Add_BulletImage(i, 0);
	for (int i = 252; i < 254; i++) Player[0]->Add_BulletImage(i, 1);
	#pragma endregion Add Texture

	#pragma region Jason

	//standing
	sprites->Add(1001, 3, 30, 11, 46, texJason);
	sprites->Add(1002, 30, 30, 38, 46, texJason);
	sprites->Add(1003, 21, 30, 29, 46, texJason);
	sprites->Add(1004, 12, 30, 20, 46, texJason);

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

	sprites->Add(1250, 75, 40, 79, 44, texJason);
	ani = new CAnimation(100);
	ani->Add(1250);
	animations->Add(750, ani);

	sprites->Add(1251, 140, 101, 147, 109, texJason);
	sprites->Add(1252, 149, 97, 165, 110, texJason);
	sprites->Add(1253, 166, 97, 182, 113, texJason);
	sprites->Add(1254, 166, 97, 182, 113, texJason);
	//sprites->Add(1254, 183, 93, 207, 117, texJason);
	ani = new CAnimation(100);
	for (int i = 1251; i < 1255; i++) ani->Add(i);
	animations->Add(751, ani);

	Player[1]->Add_BulletImage(750, 0);
	Player[1]->Add_BulletImage(751, 0);
	Player[0]->Add_BulletImage(751, 0);
	Player[0]->Add_BulletImage(751, 1);
	#pragma endregion Add Texture

	#pragma region JasonOW

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

	//knocked
	sprites->Add(10010, 284, 4, 307, 35, texJason);
	sprites->Add(10011, 308, 6, 332, 35, texJason);
	sprites->Add(10012, 333, 8, 356, 35, texJason);
	sprites->Add(10013, 358, 10, 382, 35, texJason);
	sprites->Add(10014, 383, 19, 407, 35, texJason);

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

	//knocked
	ani = new CAnimation(500);
	ani->Add(10010);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(1003, ani);

	Player[2]->Add_Image(1000);
	Player[2]->Add_Image(1000);
	Player[2]->Add_Image(1001);
	Player[2]->Add_Image(1002);
	Player[2]->Add_Image(1003);

	sprites->Add(752, 83, 39, 89, 45, texJason);
	ani = new CAnimation(100);
	ani->Add(752);
	animations->Add(752, ani);

	sprites->Add(753, 252, 106, 260, 114, texJason);
	ani = new CAnimation(100);
	ani->Add(753);
	animations->Add(753, ani);

	Player[2]->Add_BulletImage(752, 0);
	Player[2]->Add_BulletImage(752, 0);
	Player[2]->Add_BulletImage(751, 0);
	#pragma endregion Add Texture

}

void MainPlayer::Update(DWORD dt, vector<GameObject*> coObjects)
{
	UINT ItemsIgnored = coObjects.size() - ItemSize;
	vector<GameObject*> RawcoObjects;
	for (UINT i = 0; i < ItemsIgnored; i++)
	{
		RawcoObjects.push_back(coObjects[i]); //Weapon won't be able to hit items
	}
	Player[curPlayer]->Update(dt, &coObjects);
	Player[curPlayer]->UpdateWeapon(dt, &RawcoObjects);
	if (curPlayer == 1)
	{
		Player[0]->UpdateWeapon(dt, &RawcoObjects);
		Player[0]->Update(dt,&RawcoObjects);
	}
	if (curPlayer == 0)
	{
		Player[1]->UpdateWeapon(dt, &RawcoObjects);
		//Player[1]->Update(dt);
	}
}

void MainPlayer::Render()
{
	if (curPlayer == 1)
	{
		Player[0]->Render();
		Player[0]->RenderWeapon();
	}
	if (curPlayer == 0)
	{
		if (Player[0]->GetJasonState() == false) Player[1]->Render();
		Player[1]->RenderWeapon();
	}
	Player[curPlayer]->Render();
	Player[curPlayer]->RenderWeapon();
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
