#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Camera.h"
#include "BoundingBox.h"
#include "KeyEventHandler.h"

#define KEYBOARD_BUFFER_SIZE 1024

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	Camera cam;

public:
	void InitKeyBoard(LPKEYEVENTHANDLER handler);
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom,int DrawCenterType,bool FlipHorizontal,int RenderColor);
	void DrawHealthbars(LPDIRECT3DTEXTURE9 texture,int Value);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	static void SweptAABB(
		BoundingBox* MoveObject,
		float dx,			// 
		float dy,			// 
		BoundingBox* StaticObject,
		float &t,
		float &nx,
		float &ny);

	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR texturePath);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	HWND getHWND() { return this->hWnd; }

	D3DXVECTOR2 FromWorldToRender(float x,float y);
	void SetCamPos(float x, float y);
	float Get_CamX() { return this->cam.get_x(); }
	float Get_CamY() { return this->cam.get_y(); }

	static CGame* GetInstance();

	~CGame();
};

