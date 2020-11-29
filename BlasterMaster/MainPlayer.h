#pragma once
#include "Jason.h"
#include "JasonOW.h"
#include "Sophia.h"

class MainPlayer
{
private:
	vector<ControllableChar*> Player;
	LPDIRECT3DTEXTURE9 texSophia;
	LPDIRECT3DTEXTURE9 texJason;
	LPDIRECT3DTEXTURE9 texItem;
	int curPlayer = 0;
	int ItemSize = 0;
	static MainPlayer* _instance;
public:
	MainPlayer();
	void LoadTexture();
	void Update(DWORD dt, vector<GameObject*> coObject);
	void Render();

	void SetAni(int ani);
	void SetPos(float x, float y) { Player[curPlayer]->SetPos(x, y); }
	void SetPlayer(int cur) { if (cur >= 0 && cur < 3) this->curPlayer = cur; }
	void SetReleaseKey(int Reaction) { if(Reaction !=-1) Player[0]->SetReleaseKey(Reaction); }
	void SetItemSize(int is) { this->ItemSize = is; }
	void SetSpecialWeapon(int spw) { Player[curPlayer]->SetSpeacialWeapon(spw); }
	void SetFlagBosFight(bool fbf) { Player[curPlayer]->SetFlagBossFight(fbf); }\
	void SetFlagDead(bool fd) { Player[curPlayer]->SetFlagDead(fd); }

	bool GetFallingState() { return Player[curPlayer]->IsFallingDown(); }
	GameObject* Get_CurPlayerInfo() { return Player[curPlayer]; }
	int Get_CurPlayer() { return curPlayer; }
	int Get_CurPlayerHP() { return Player[curPlayer]->GetHP(); }
	float Get_CurPlayer_lastX() { return Player[curPlayer]->Get_lastx(); }
	float Get_CurPlayer_lastY() { return Player[curPlayer]->Get_lasty(); }
	float Get_Player_X(int player) { return Player[player]->Get_x(); }
	float Get_Player_Y(int player) { return Player[player]->Get_y(); }
	int GetCurWeapon() { return Player[curPlayer]->GetCurWeapon(); }
	bool GetBossFight() { return Player[curPlayer]->GetFlagBossFight(); }
	bool GetFlagDead() { return Player[curPlayer]->GetFlagDead(); }
	BoundingBox* GetBB(int player) { return Player[player]->GetBoundingBox(); }
	static MainPlayer* GetInstance();
};
