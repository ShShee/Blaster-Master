#pragma once
#include "Textures.h"
#include "Enemies.h"

class Bullet :public MovingObject
{
protected:
	bool FlipX = true;
	float limitationX;
	float limitationY;
	int type;
	bool FlagCollision = false;
	bool FlagLimit = false;
	float x_target;
	float y_target;
public:
	Bullet(float x, float y, float vx, float vy, int type)
		:MovingObject(x, y, vx, vy) {
		this->type = type;
		SetLimitationByType(this->type);
	}
	virtual void Update(DWORD dt, vector<GameObject*>* coObject);
	void Render();

	void SetLimit(float x, float y) { limitationX = x; limitationY = y; }
	void SetFlip(bool FlipFlag);
	void SetFlagLimit(bool fl) { FlagLimit = fl; }
	void SetLimitationByType(int type);

	bool GetFlagLimit() { return FlagLimit; }
	bool GetFlagCollision() { return FlagCollision; }
	int GetType() { return type; }
	float GetLimitation_X() { return limitationX; }
	float GetLimitation_Y() { return limitationY; }
	bool IsStopped() { if (vx == 0 && vy == 0) return true; else return false; }
	void LocateTarget(float x, float y) { this->x_target = x; this->y_target = y; }
};

class HomingMissile : public Bullet
{
protected:
	int IdTarget = 1000;
public:
	HomingMissile(float x, float y, float vx, float vy, int type) :Bullet(x, y, vx, vy, type) {}
	void Update(DWORD dt, vector<GameObject*>* coObject);
	void LockIdTarget(int id) { this->IdTarget = id; }
	//void Render();
};
class Weapon
{
private:
	vector<Bullet*> BulletCount;
	vector<int> BulletID;
public:
	Weapon() {}
	void Update(DWORD dt, vector <GameObject*>* coObject);
	void Render();

	void AddBulletId(int id);
	void AddBullet(int WeaponType, int curBullet, float x, float y, float vx, float vy, bool FlipX = false, int type = 0);
	bool IsAbletoMove() { return true; }
	bool IsBulletNull() { return !(BulletCount.size() > 0); }
	void SetTarget(float x, float y) { BulletCount[BulletCount.size() - 1]->LocateTarget(x, y); }
};

class Enemy_With_Weapon
{
protected:
	Weapon wp;
	float CoolDown = 0;
	float vtCD = 0.5f;
public:
	void CreateSprite();
	void Render() { wp.Render(); }
};

class Enemy_Bomber : public CAWA_Enemy,public Enemy_With_Weapon
{
private:
	bool FlagFire = false;
public:
	Enemy_Bomber(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		wp.AddBulletId(Bomber_Bullet);
		wp.AddBulletId(751);
	}
	void Update(DWORD dt, vector<GameObject*>* coOBject, float x_target, float y_target);
	void Render() { if (HealthPoint > 0) { Enemy::Render(); Enemy_With_Weapon::Render(); } }
};

class Enemy_Floater : public CAWA_Enemy, public Enemy_With_Weapon
{
public:
	Enemy_Floater(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
		CreateSprite();
	}
	void Update(DWORD dt, vector<GameObject*>* coOBject, float x_target, float y_target);
	void Render() { if (HealthPoint > 0) { Enemy::Render(); Enemy_With_Weapon::Render(); } }
};

class Enemy_Cannon : public CAWA_Enemy,public Enemy_With_Weapon
{
private:
	bool FlagFired = false;
public:
	Enemy_Cannon(float x = 0, float y = 0, bool DrawCenter = false)
		:CAWA_Enemy(x, y, 0, 0, 0, 0, DrawCenter) {
		wp.AddBulletId(753);
		CreateSprite();
		CoolDown = 6000;
		vtCD = 0.5f;
	}
	void Update(DWORD dt, vector<GameObject*>* coOBject);
	void Render() { if (HealthPoint > 0) { Enemy::Render(); Enemy_With_Weapon::Render(); } }
};

class Enemy_EyeBall : public Enemy_Floater
{
public:
	Enemy_EyeBall(float x = 0, float y = 0, float vx = 0, float vy = 0, float limited_move_x = 0, float limited_move_y = 0, bool DrawCenter = false)
		:Enemy_Floater(x, y, vx, vy, limited_move_x, limited_move_y, DrawCenter) {
	}
};

class ControllableChar :public MovingObject
{
protected:
	int lastAni = 0;

	STATE* status;
	vector<Weapon*>WeaponType;
	int BulletFired = 0;
	int curWeapon=0; //current weapon level
	
	bool IsUpReleased = false;
	bool IsFalling = false;
	bool IsJasonBack = true;
	bool IsBlocked = false;
	bool FlagAutomatic = false; //use when go through door

	float timerCD = 0; //timer cooldown bullet
	float vtCD; //start cooldown bullet

	float timerCS = 0;
	float timeCSlimit;
	float vtCS = 0;
public:
	ControllableChar();
	virtual void Update(DWORD dt, vector<GameObject*> *coObject = NULL);
	void UpdateWeapon(DWORD dt,vector<GameObject*> *coObject=NULL);
	virtual void Render() = 0;
	void RenderWeapon();
	virtual void SetAni(int ani) = 0;
	virtual void ResetLife();
	void Add_BulletImage(int id,int weapontype);
	bool LockCam(float x, float y);

	void SetSpeacialWeapon(int spw) { this->curWeapon = spw; }
	void SetNormalUpdate() { x += dx; y += dy; }
	void SetReleaseKey(int Reaction) { if (Reaction == 2) IsUpReleased = true; }
	bool IsFallingDown() { return IsFalling; }

	bool GetJasonState() { return IsJasonBack; }
	int GetCurWeapon() { return this->curWeapon; }
};





