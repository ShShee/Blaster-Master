#pragma once
#include <Windows.h>
#include <dinput.h>

class KeyEventHandler
{
protected:
	int State=-1;
	int ReleasedKeyState;
	int SpecialWeapon=0;
	bool Switch = false;
	bool FlagScene = false;

	D3DXVECTOR2 Position;
	bool FlagSetPos = false;
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	void SetState(int st) { this->State = st; }
	int GetState() { return this->State; }

	void SetReleasedState(int st) { this->ReleasedKeyState = st; }
	int GetReleasedState() { int temp = ReleasedKeyState; ReleasedKeyState = -1; return temp; }

	void SetSpecialWeapon(int st) { if (st == SpecialWeapon) this->SpecialWeapon = 0; else this->SpecialWeapon = st; }
	int GetSpecialWeapon() { return this->SpecialWeapon; }

	void SetPos(D3DXVECTOR2 pos) { this->Position = pos; }
	void SetFlagPos() { this->FlagSetPos = true; }
	bool GetFlagPos() { return this->FlagSetPos; }
	D3DXVECTOR2 GetPos() { FlagSetPos = false;  return this->Position; }

	void SetSwitch() { this->Switch = true; }
	bool GetSwitch() { bool temp = Switch; if(Switch==true) Switch = false; return temp; }

	void SetFlagScene(bool fs=true) { this->FlagScene = fs; }
	bool GetFlageScene() { return this->FlagScene; }
};

typedef KeyEventHandler* LPKEYEVENTHANDLER;

//


