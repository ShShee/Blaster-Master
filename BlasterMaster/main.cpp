#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "GameObject.h"
#include "Textures.h"
#include "Game.h"
#include "Enemies.h"
#include "ControllableChar.h"
#include "WorldMap.h"
#include "Quadtree.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(69,255,69)
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

#define MAX_FRAME_RATE 60


CGame* game;
vector<GameObject*>SaveForTheLast;
Quadtree* quadtree = new Quadtree(1, new BoundingBox(0, 0, 2048, 2048));
//Sophia* sophia = new Sophia(20.0f,20.0f);
//UnmovingObject* map = new UnmovingObject(0.0f,2048.0f);
vector<GameObject*> ListObject;
MainPlayer* ReadyPlayer1 = new MainPlayer();

Enemy_Jumper* jumper = new Enemy_Jumper(1000.0f, 500.0f, 0.02f, 295.0f, true);

Enemy_Bomber* bomber = new Enemy_Bomber(1700.0f, 1800.0f, 0.01f, NULL, 285.0f, 40.0f);

Enemy_Orb* orb = new Enemy_Orb(100.0f, 100.0f, 0.03f, 0.0f, 100.0f, 100.0f, true);

WorldMap* wm = new WorldMap();

class CSampleKeyHander : public KeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		ReadyPlayer1->SetAni(JUMP);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	OutputDebugString(L"[INFO] KeyUp: %d\n");
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	if (game->IsKeyDown(DIK_RIGHT))
		ReadyPlayer1->SetAni(GO_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		ReadyPlayer1->SetAni(GO_LEFT);
	else if (game->IsKeyDown(DIK_UP))
		ReadyPlayer1->SetAni(GO_UP);
	else if (game->IsKeyDown(DIK_DOWN))
		ReadyPlayer1->SetAni(GO_DOWN);
	else ReadyPlayer1->SetAni(IDLE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_ENEMY, L"SpritesSource\\Enemies.png", D3DCOLOR_XRGB(255, 255, 255));
	ReadyPlayer1->LoadTexture();
	wm->LoadMap("SpritesSource\\area2map.tmx");

	CSprites* sprites = CSprites::GetInstance();

	
	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	//LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_TEX_TILESET);

	//sprites->Add(4000, 0, 0, 16, 16, texMap);
	//Sophia

	//core

	//Jason


	//orb
    sprites->Add(2061, 158, 387, 176, 405, texEnemy);
	sprites->Add(2062, 98, 387, 116, 405, texEnemy);
	sprites->Add(2063, 118, 387, 136, 405, texEnemy);
	sprites->Add(2064, 138, 387, 156, 405, texEnemy);
	sprites->Add(2065, 78, 387, 96, 405, texEnemy);

	//jumper
	sprites->Add(2001, 132, 500, 149, 525, texEnemy);
	sprites->Add(2002, 152, 499, 167, 525, texEnemy);
	sprites->Add(2003, 170, 500, 185, 525, texEnemy);

	sprites->Add(2004, 105, 500, 122, 525, texEnemy);
	sprites->Add(2005, 87, 499, 102, 525, texEnemy);
	sprites->Add(2006, 69, 500, 84, 525, texEnemy);

	//bomber
	sprites->Add(2011, 194, 530, 212, 548, texEnemy);
	sprites->Add(2012, 174, 527, 192, 548, texEnemy);

	sprites->Add(2013, 42, 530, 60, 548, texEnemy);
	sprites->Add(2014, 62, 527, 80, 548, texEnemy);

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;
	//Sophia
	ReadyPlayer1->SetPlayer(0);
	ReadyPlayer1->SetPos(1000.0f, 500.0f);

	ani = new CAnimation(200);
	ani->Add(2061);
	ani->Add(2062);
	ani->Add(2063);
	ani->Add(2064);
	animations->Add(214, ani);

	ani = new CAnimation(200);
	ani->Add(2065);
	ani->Add(2064);
	ani->Add(2063);
	ani->Add(2062);
	animations->Add(215, ani);

	orb->Add_Image(214);
	orb->Add_Image(215);

	//jumper
	ani = new CAnimation(100);
	ani->Add(2001);
	ani->Add(2002);
	ani->Add(2003);
	animations->Add(200, ani); //walking toward right

	ani = new CAnimation(100);
	ani->Add(2004);
	ani->Add(2005);
	ani->Add(2006);
	animations->Add(201, ani); //walking toward left

	//bomber
	ani = new CAnimation(100);
	ani->Add(2011);
	ani->Add(2012);
	animations->Add(202, ani);

	ani = new CAnimation(100);
	ani->Add(2013);
	ani->Add(2014);
	animations->Add(203, ani);

	jumper->Add_Image(200);
	jumper->Add_Image(201);

	bomber->Add_Image(202);
	bomber->Add_Image(203);

	wm->SetListItem();

	for(GameObject* gobj:wm->GetListMapItem())
	{
		quadtree->Insert(gobj);
	}
	//map->Add_Image(3000);
	quadtree->Insert(orb);
	quadtree->Insert(jumper);
	quadtree->Insert(bomber);
	
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	ReadyPlayer1->Update(dt);
	//ListObject.clear();
	//quadtree->Retrieve(ListObject, jason);
	//sophia->Update(dt);
	/*orb->Update(dt, jasonOW->Get_x(), jasonOW->Get_y());*/
	//map->Update(dt);

	CGame::GetInstance()->SetCamPos(ReadyPlayer1->Get_CurPlayer_X() - SCREEN_WIDTH / 2, ReadyPlayer1->Get_CurPlayer_Y()+SCREEN_HEIGHT/2);

	ListObject.clear();

	quadtree->GetListObjectinCamera(ListObject, 
		new BoundingBox(CGame::GetInstance()->Get_CamX(), 2032-CGame::GetInstance()->Get_CamY()>SCREEN_HEIGHT ? (2032 - CGame::GetInstance()->Get_CamY())- SCREEN_HEIGHT : 0,
		SCREEN_WIDTH, SCREEN_HEIGHT));
	for (GameObject* gobj : ListObject)
	{
		if (gobj->IsAbletoMove() == true)
			gobj->Update(dt, ReadyPlayer1->Get_CurPlayer_X(), ReadyPlayer1->Get_CurPlayer_Y());
	}
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		//map->Render();
		/*for (int i = 0; i < 24; i++) bricks[i]->Render();*/
		
		//wm->Render();
		//wm->SetListItem();
		//quadtree->Retrieve(ListObject, jason);
		//CSprites::GetInstance()->Get(3000)->Draw(10, 10);
		
 		//quadtree->Render();
		for (GameObject* gobj : ListObject)
		{
			if (gobj->IsAbletoMove() == true)
				SaveForTheLast.push_back(gobj);
			else gobj->Render();
		}
		ReadyPlayer1->Render();
		for (GameObject* gobj : SaveForTheLast)
		{
			gobj->Render();
		}
		SaveForTheLast.clear();
		//sophia->Render();
		//orb->Render();
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyBoard(keyHandler);

	LoadResources();
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	Run();


	return 0;
}