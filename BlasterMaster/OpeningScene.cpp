#include "OpeningScene.h"

OpeningScene::OpeningScene()
{
	keyHandler = new NextKeyHandler();
}

void OpeningScene::Update(DWORD dt)
{
	timer += vt * dt;
	CGame::GetInstance()->SetCamPos(300.0f, 300.0f);
	if (keyHandler->GetState() == 8)
	{
		if (currentAni == 1) {
			IntroParts[currentAni]->SetCurrentFrame(IntroParts[currentAni]->GetFrameSize()-1); /*currentAni = 1;*/
		}
		else if (currentAni == 0)
		{
			currentAni = 2;
			Sound::getInstance()->play("runin", true, 0);
		}
		keyHandler->SetState(IDLE);
	}

	if ((IntroParts[currentAni]->GetCurrentFrame() == IntroParts[currentAni]->GetFrameSize() - 1))
	{
		if (currentAni == 1)
		{
			currentAni = 0;
			timer = -1000;
			vt = 0.5f;
			Sound::getInstance()->stop("opening");
		}
		else if (currentAni == 2)
		{
			FlagChangeScene = true;
		}
	}
	else if (timer > 2000 && currentAni==0)
	{
		Sound::getInstance()->play("opening", true, 0);
		currentAni = 1;
		vt = 0;
	}

	switch (currentAni)
	{
	case 0:
		locationX = 300;
		locationY = 320;
		break;
	default:
		locationX = 315;
		locationY = 280;
		break;
	}
}

void OpeningScene::LoadContent()
{
	CTextures::GetInstance()->Add(ID_TEX_PLAY, L"SpritesSource\\Play.png", D3DCOLOR_XRGB(54, 115, 1));
	CTextures::GetInstance()->Add(ID_TEX_OPENING, L"SpritesSource\\Opening.png", D3DCOLOR_XRGB(54, 115, 1));
	CTextures::GetInstance()->Add(ID_TEX_INTRO, L"SpritesSource\\Intro.png", D3DCOLOR_XRGB(54, 115, 1));

	texPlay = CTextures::GetInstance()->Get(ID_TEX_PLAY);
	texOpening = CTextures::GetInstance()->Get(ID_TEX_OPENING);
	texIntro = CTextures::GetInstance()->Get(ID_TEX_INTRO);

	CSprites* sprites = CSprites::GetInstance();
	LPANIMATION ani;

	//sprites->Add(95000, 0, 0, 256, 224, texOpening);
	//sprites->Add(95001, 259,0, 515, 224, texOpening);
	sprites->Add(95002, 518, 0, 774, 224, texOpening);
	sprites->Add(95003, 777, 0, 1033, 224, texOpening);

	//sprites->Add(95004, 0, 227, 256, 451, texOpening);
	//sprites->Add(95005, 259, 227, 515, 451, texOpening);
	sprites->Add(95006, 518, 227, 774, 451, texOpening);
	sprites->Add(95007, 777, 227, 1033, 451, texOpening);

	//sprites->Add(95008, 0, 454, 256, 678, texOpening);
	//sprites->Add(95009, 259, 454, 515, 678, texOpening);
	sprites->Add(95010, 518, 454, 774, 678, texOpening);
	sprites->Add(95011, 777, 454, 1033, 678, texOpening);

	//sprites->Add(95012, 0, 681, 256, 905, texOpening);
	//sprites->Add(95013, 259, 681, 515, 905, texOpening);
	sprites->Add(95014, 518, 681, 774, 905, texOpening);
	sprites->Add(95015, 777, 681, 1033, 905, texOpening);

	sprites->Add(95016, 0, 908, 256, 1132, texOpening);
	sprites->Add(95017, 259, 908, 515, 1132, texOpening);
	//sprites->Add(95018, 518, 908, 774, 1132, texOpening);
	//sprites->Add(95019, 777, 908, 1033, 1132, texOpening);

	//sprites->Add(95020, 0, 1135, 256, 1359, texOpening);
	//sprites->Add(95021, 259, 1135, 515, 1359, texOpening);
	//sprites->Add(95022, 518, 1135, 774, 1359, texOpening);
	sprites->Add(95023, 777, 1135, 1033, 1359, texOpening);

	sprites->Add(95024, 0, 1362, 256, 1586, texOpening);
	//sprites->Add(95025, 259, 1362, 515, 1586, texOpening);
	//sprites->Add(95026, 518, 1362, 774, 1586, texOpening);
	sprites->Add(95027, 777, 1362, 1033, 1586, texOpening);

	sprites->Add(95028, 0, 1589, 256, 1813, texOpening);
	//sprites->Add(95029, 259, 1589, 515, 1813, texOpening);
	//sprites->Add(95030, 518, 1589, 774, 1813, texOpening);
	sprites->Add(95031, 777, 1589, 1033, 1813, texOpening);

	sprites->Add(95032, 0, 1816, 256, 2040, texOpening);
	//sprites->Add(95033, 259, 1816, 515, 2040, texOpening);
	//sprites->Add(95034, 518, 1816, 774, 2040, texOpening);
	sprites->Add(95035, 777, 1816, 1033, 2040, texOpening);

	sprites->Add(95036, 0, 2043, 256, 2267, texOpening);

	sprites->Add(95037, 0, 0, 300, 300, texPlay);
	sprites->Add(95038, 0, 313, 300, 613, texPlay);
	sprites->Add(95039, 378, 316, 678, 616, texPlay);
	sprites->Add(95040, 378, 1, 678, 301, texPlay);

	sprites->Add(95041, 0, 0, 256, 224, texIntro);
	sprites->Add(95042, 259, 0, 515, 224, texIntro);
	sprites->Add(95043, 518, 0, 774, 224, texIntro);

	sprites->Add(95044, 0, 227, 256, 451, texIntro);
	sprites->Add(95045, 259, 227, 515, 451, texIntro);
	sprites->Add(95046, 518, 227, 774, 451, texIntro);

	sprites->Add(95047, 0, 454, 256, 678, texIntro);
	sprites->Add(95048, 259, 454, 515, 678, texIntro);
	sprites->Add(95049, 518, 454, 774, 678, texIntro);

	sprites->Add(95050, 0, 681, 256, 905, texIntro);

	ani = new CAnimation(100);
	ani->Add(95037);
	ani->Add(95038);
	ani->Add(95039);
	ani->Add(95040);
	IntroParts.push_back(ani);

	ani = new CAnimation(2000);
	/*for(UINT i=95000;i<95037;i++)	ani->Add(i);*/
	ani->Add(95002);
	ani->Add(95003);
	ani->Add(95007);
	ani->Add(95011);
	ani->Add(95015);
	ani->Add(95016);
	ani->Add(95017);
	ani->Add(95024);
	ani->Add(95028);
	ani->Add(95032); 
	ani->Add(95036);
	ani->Add(95036);
	IntroParts.push_back(ani);

	ani = new CAnimation(50);
	/*for(UINT i=95000;i<95037;i++)	ani->Add(i);*/
	ani->Add(95041);
	ani->Add(95042);
	ani->Add(95041);
	ani->Add(95042);
	ani->Add(95041);
	ani->Add(95042);
	ani->Add(95041);
	ani->Add(95042);
	ani->Add(95041);
	ani->Add(95042);
	ani->Add(95041);
	ani->Add(95042);
	ani->Add(95043);
	ani->Add(95044);
	ani->Add(95045);
	ani->Add(95046);
	ani->Add(95047);
	ani->Add(95048);
	ani->Add(95049);
	ani->Add(95050);
	ani->Add(95050);
	ani->Add(95050);
	IntroParts.push_back(ani);
}

void OpeningScene::Render()
{
	IntroParts[currentAni]->Render(locationX, locationY, -1, 0, false, 255, 255);
}
