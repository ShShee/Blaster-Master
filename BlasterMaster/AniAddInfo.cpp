////jumper
//ani = new CAnimation(100);
//ani->Add(2001);
//ani->Add(2002);
//ani->Add(2003);
//animations->Add(200, ani); //walking toward right
//
//ani = new CAnimation(100);
//ani->Add(2004);
//ani->Add(2005);
//ani->Add(2006);
//animations->Add(201, ani); //walking toward left
//
////bomber
//ani = new CAnimation(100);
//ani->Add(2011);
//ani->Add(2012);
//animations->Add(202, ani);
//
//ani = new CAnimation(100);
//ani->Add(2013);
//ani->Add(2014);
//animations->Add(203, ani);
//
////worm
//ani = new CAnimation(100);
//ani->Add(2021);
//ani->Add(2022);
//animations->Add(204, ani);
//
//ani = new CAnimation(100);
//ani->Add(2023);
//ani->Add(2024);
//animations->Add(205, ani);
//
////floater
//ani = new CAnimation(100);
//ani->Add(2031);
//ani->Add(2032);
//animations->Add(206, ani);
//
//ani = new CAnimation(100);
//ani->Add(2033);
//ani->Add(2034);
//animations->Add(207, ani);
//
////insect
//ani = new CAnimation(300);
//ani->Add(2041);
//ani->Add(2042);
//animations->Add(208, ani);
//
//ani = new CAnimation(300);
//ani->Add(2043);
//ani->Add(2044);
//animations->Add(209, ani);
//
////wall-walkers
//ani = new CAnimation(100);
//ani->Add(2051);
//ani->Add(2052);
//animations->Add(210, ani); //walking normal
//
//ani = new CAnimation(100);
//ani->Add(2053);
//ani->Add(2054);
//animations->Add(211, ani); //walking down
//
//ani = new CAnimation(100);
//ani->Add(2055);
//ani->Add(2056);
//animations->Add(212, ani);//walking upside down
//
//ani = new CAnimation(100);
//ani->Add(2057);
//ani->Add(2058);
//animations->Add(213, ani);//walking up
//
////orb
//ani = new CAnimation(200);
//ani->Add(2061);
//ani->Add(2062);
//ani->Add(2063);
//ani->Add(2064);
//animations->Add(214, ani);
//
//ani = new CAnimation(200);
//ani->Add(2065);
//ani->Add(2064);
//ani->Add(2063);
//ani->Add(2062);
//animations->Add(215, ani);
//
//ani = new CAnimation(300);
//ani->Add(2061);
//ani->Add(2062);
//ani->Add(2063);
//ani->Add(2064);
//ani->Add(2065);
//animations->Add(216, ani);
//
//jumper->Add_Image(200);
//jumper->Add_Image(201);
//
//bomber->Add_Image(202);
//bomber->Add_Image(203);
//
//worm->Add_Image(204);
//worm->Add_Image(205);
//
//floater->Add_Image(206);
//floater->Add_Image(207);
//
////insect->Add_Image(208);
////insect->Add_Image(209);
//
//dome->Add_Image(210);
//dome->Add_Image(211);
//dome->Add_Image(212);
//dome->Add_Image(213);
//
//orb->Add_Image(214);
//orb->Add_Image(215);
//orb->Add_Image(216);
//
////eyeball
//ani = new CAnimation(600);
//ani->Add(2068);
//ani->Add(2067);
//ani->Add(2068);
//ani->Add(2067);
//ani->Add(2068);
//ani->Add(2067);
//ani->Add(2069);
//animations->Add(217, ani);
//
//eyeball->Add_Image(217);
//
////cannon
//ani = new CAnimation(600);
//ani->Add(2070);
//ani->Add(2071);
//ani->Add(2070);
//ani->Add(2072);
//animations->Add(218, ani);
//
//
//cannon->Add_Image(218);
//
////tele
//ani = new CAnimation(300);
//ani->Add(2074);
//ani->Add(2073);
//animations->Add(219, ani);
//
//
//tele->Add_Image(219);
//
//GameObject* brick;
//for (int i = 0; i < 24; i++)
//{
//	if (i < 20) brick = new UnmovingObject(16.0f * i, 155.0f);
//	else if (i >= 20 && i < 22) brick = new UnmovingObject(16.0f * (i - 7), 70.0f);
//	else brick = new UnmovingObject(16.0f * (i - 16), 70.0f);
//	brick->Add_Image(30001);
//	bricks.push_back(brick);
//}
