#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>


using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y,bool DrawCenter=false,bool flipX=false);

	int GetWidth() {return this->right; }
	int GetHeight() { return this->bottom; }
};

typedef CSprite* LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static CSprites* GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
	int GetWidth() { return sprite->GetWidth(); }
	int GetHeight() { return sprite->GetHeight(); }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y,int designatedFrame=-1,bool DrawCenter=false,bool flipX=false);
	void SetCurrentFrame(unsigned int curFrame) { if (curFrame>frames.size()) curFrame = -1; this->currentFrame = curFrame; }
	int GetCurrentFrame() { return this->currentFrame; }
	int GetWidth() {if (currentFrame == -1) currentFrame = 0; return frames[currentFrame]->GetWidth(); }
	int GetHeight() {if (currentFrame == -1) currentFrame = 0; return frames[currentFrame]->GetHeight(); }
};

typedef CAnimation* LPANIMATION;

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations* GetInstance();
};


