#include "Game.h"

CGame* CGame::__instance = NULL;


D3DXVECTOR2 CGame::FromWorldToRender(float x,float y)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = 0;
	mt._42 = 2032;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos,&D3DXVECTOR3(x,y,0),&mt);
	return D3DXVECTOR2(vp_pos.x,vp_pos.y);
}

void CGame::InitKeyBoard(LPKEYEVENTHANDLER handler)
{
	HRESULT
		hr = DirectInput8Create
		(
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		OutputDebugString(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		OutputDebugString(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	this->keyHandler = handler;

	OutputDebugString(L"[INFO] Keyboard has been initialized successfully\n");
}

void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom,int DrawCenterType,bool FlipHorizontal,int RenderColor,int transparentcy)
{
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	float Half_Width = (float)((r.right - r.left) / 2);
	float Half_Height = (float)((r.bottom - r.top) / 2);
	D3DXVECTOR3 center(Half_Width, Half_Height, 0);
	D3DXVECTOR2 translate = FromWorldToRender(x, y);
	if (DrawCenterType == 1)
	{
		translate.x += Half_Width;
		translate.y += Half_Height;
	}
	D3DXVECTOR3 p(floor(translate.x-cam.get_x()),floor(translate.y-cam.get_y()), 0);
	D3DXMATRIX oldMatrix,transform;
	spriteHandler->GetTransform(&oldMatrix);
	D3DXVECTOR2 ScalingCenter,Scale,RotationCenter,Translation;
	if (FlipHorizontal == true)
	{
		ScalingCenter = D3DXVECTOR2(floor(translate.x-cam.get_x()), floor(translate.y - cam.get_y()));
		Scale = D3DXVECTOR2(-1,1);
		RotationCenter = D3DXVECTOR2(0, 0);
		Translation = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&transform, &ScalingCenter, 0, &Scale, &RotationCenter, 0, &Translation);
		spriteHandler->SetTransform(&transform);
	}
	DrawCenterType == 0 ? spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(transparentcy,255, RenderColor, RenderColor)) 
		: spriteHandler->Draw(texture, &r, &center, &p, D3DCOLOR_ARGB(transparentcy,255, RenderColor, RenderColor));
	spriteHandler->SetTransform(&oldMatrix);
}

void CGame::DrawHealthbars(LPDIRECT3DTEXTURE9 texture,int Value)
{
	int HealthHeight= 0, HHeight = 0;
	Draw(cam.get_x() + 13.0f, 2032.0f - cam.get_y() - 50.0f, texture, 55, 1, 69, 34, false, false, 255,255);
	Draw(cam.get_x() + 13.0f, 2032.0f - cam.get_y() - 205.5f, texture, 55, 35, 69, 68, false, false, 255,255);
	Draw(cam.get_x() + 12.0f, 2032.0f - cam.get_y() - 125.0f, texture, 17, 0, 33, 80, false, false, 255,255);
	for (int i = 8; i > 0; i--)
	{
		if (Value == i)
		{
			HealthHeight = 2032.0f - cam.get_y() - (205.0f - i * 10.0f);
			HHeight = i * 10;
		}
	}
	if(HHeight!=0) Draw(cam.get_x() + 12.0f, HealthHeight, texture, 34, 0, 50, HHeight, false, false, 255,255);
	Draw(cam.get_x() + 12.0f, 2032.0f- cam.get_y() - 125.0f, texture, 0, 0, 16, 80, false, false, 255,255);
}

int CGame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CGame::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				OutputDebugString(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE*)&keyStates);



	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

/*
	Utility function to load texture
*/
LPDIRECT3DTEXTURE9 CGame::LoadTexture(LPCWSTR texturePath)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] GetImageInfoFromFile failed");
		return NULL;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed. File");
		return NULL;
	}

	OutputDebugString(L"[INFO] Texture loaded Ok");
	return texture;
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
	if (di != NULL) di->Release();
	if (didv != NULL) didv->Release();
}


void CGame::SetCamPos(float x, float y)
{
	D3DXVECTOR2 translate = CGame::GetInstance()->FromWorldToRender(x, y);
	cam.SetCamPos(translate.x, translate.y);
}

/*
	SweptAABB
*/

void CGame::SweptAABB(
	BoundingBox* MoveObject,
	float dx, float dy,
	BoundingBox* StaticObject,
	float &t, float &nx, float &ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? MoveObject->x : MoveObject->x + dx;
	float bt = dy < 0 ? MoveObject->y : MoveObject->y + dy;
	float br = dx > 0 ? MoveObject->x + MoveObject->width + dx  : MoveObject->x + MoveObject->width;
	float bb = dy < 0 ? (MoveObject->y - MoveObject->height) + dy : MoveObject->y - MoveObject->height;

	if (br < StaticObject->x || bl > StaticObject->x+StaticObject->width 
	|| bb > StaticObject->y || bt < StaticObject->y - StaticObject->height) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = StaticObject->x - (MoveObject->x+MoveObject->width);
		dx_exit = (StaticObject->x + StaticObject->width) - MoveObject->x;
	}
	else if (dx < 0)
	{
		dx_entry = (StaticObject->x + StaticObject->width) - MoveObject->x;
		dx_exit = StaticObject->x - (MoveObject->x + MoveObject->width);
	}


	if (dy > 0)
	{
		dy_entry = (StaticObject->y - StaticObject->height) - MoveObject->y;
		dy_exit = StaticObject->y - (MoveObject->y - MoveObject->height);
	}
	else if (dy < 0)
	{
		dy_entry = StaticObject->y - (MoveObject->y - MoveObject->height);
		dy_exit = (StaticObject->y - StaticObject->height) - MoveObject->y;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f)
	{
		return;
	}
	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}
CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}