#pragma once
#include "GameObject.h"
#include "Textures.h"
class ControllableChar :public MovingObject
{
protected:
	int lastAni = 0;
	STATE* status;
	vector<GameObject*>Bullet;
public:
	ControllableChar() {
		status = new STATE; *status = NOTHING;
	}
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void SetAni(int ani) = 0;
};


class Sophia : public ControllableChar
{
protected:
	int lastFrame = 0;
public:
	Sophia() :ControllableChar() {}
	void Update(DWORD dt);
	void Render();
	void SetAni(int ani);
};


class Jason : public ControllableChar
{
public:
	Jason() :ControllableChar() {}
	void Update(DWORD dt);
	void Render();
	void SetAni(int ani);
};


class JasonOW : public ControllableChar
{
private:
	static JasonOW* _instance;
public:
	JasonOW() :ControllableChar() {};
	void Update(DWORD dt);
	void Render();
	void SetAni(int ani);
};

class MainPlayer
{
private:
	vector<ControllableChar*> Player;
	LPDIRECT3DTEXTURE9 texSophia;
	LPDIRECT3DTEXTURE9 texJason;
	int curPlayer = 0;
	static MainPlayer* _instance;
public:
	MainPlayer();
	void LoadTexture();
	void Update(DWORD dt);
	void Render();
	void SetAni(int ani);
	void SetPos(float x, float y) { Player[curPlayer]->SetPos(x, y); }
	void SetPlayer(int cur) { if(cur>=0 && cur<3) this->curPlayer = cur; }

	float Get_CurPlayer_X() { return Player[curPlayer]->Get_x(); }
	float Get_CurPlayer_Y() { return Player[curPlayer]->Get_y(); }
	static MainPlayer* GetInstance();
};




