#include "ControllableChar.h"

void Weapon::Update(DWORD dt, vector<GameObject*>* coObject)
{
	for (int temp = 0; temp < BulletCount.size(); temp++)
	{
		if ((BulletCount[temp]->Get_y() < BulletCount[temp]->GetLimitation_Y()
					&& BulletCount[temp]->GetType() ==5)
				||(BulletCount[temp]->Get_x() > BulletCount[temp]->GetLimitation_X()
					&& (BulletCount[temp]->GetType() % 3 == 0))
				|| (BulletCount[temp]->Get_x() < BulletCount[temp]->GetLimitation_X()
					&& (BulletCount[temp]->GetType() % 3 == 1))
				|| (BulletCount[temp]->Get_y() > BulletCount[temp]->GetLimitation_Y()
					&& BulletCount[temp]->GetType() == 2)
				|| BulletCount[temp]->GetFlagCollision() == true)
		{
			BulletCount[temp]->SetSpeed(0, 0);
			BulletCount[temp]->SetPos(BulletCount[temp]->Get_x(), BulletCount[temp]->Get_y());
		}
	}
	if (BulletCount.size() > 0)
	{

		if (BulletCount[0]->GetFlagLimit() == false && BulletCount[0]->IsStopped() == true)
		{
			BulletCount[0]->SetAni(1);
		}
		if (BulletCount[0]->GetFlagLimit() == true)
		{
			BulletCount.erase(BulletCount.begin());
		}
	}
	for (int i = 0; i < BulletCount.size(); i++)
	{
		BulletCount[i]->Update(dt, coObject);
	}
}

void Weapon::Render()
{
	if (BulletCount.size() > 0)
	{
		for (int i = 1; i < BulletCount.size(); i++)
		{
			BulletCount[i]->Render();
		}
		BulletCount[0]->Render();
	}
}

void Weapon::AddBulletId(int id)
{
	BulletID.push_back(id);
}

void Weapon::UpgradeBulletId(int id)
{
	BulletID.pop_back();
	BulletID.push_back(id);
	UpdateLevel++;
	UpdateLevel == 1 ? damage = 3:damage=1;
}

void Weapon::AddBullet(int WeaponType, int curBullet, float x, float y, float vx, float vy, bool FlipX, int type)
{
	float limitationX = 0, limitationY = 0;

	if (WeaponType == 0)
	{
		Bullet* addblt;
		addblt = new Bullet(x, y, vx, vy, type,damage);
		addblt->Add_Image(BulletID[curBullet]);//ani 1
		if (type >=3) addblt->Add_Image(BulletID[curBullet + 1]);
		else addblt->Add_Image(BulletID[2]);//ani 2 with normal and 3 with special
		addblt->SetFlip(FlipX);
		BulletCount.push_back(addblt);
	}
	else if (WeaponType == 1)
	{
		Bullet* addblt;
		addblt = new HomingMissile(x, y, vx, vy, type,damage);
		addblt->Add_Image(BulletID[curBullet]);//ani 1

		//if (type ==1 || type ==2)
		//	(WeaponType == 1 && curBullet == 0) ? addblt->Add_Image(BulletID[1]) : addblt->Add_Image(BulletID[0]);//ani 2 with special

		if (type >=2) addblt->Add_Image(BulletID[curBullet + 1]);
		else addblt->Add_Image(BulletID[2]);//ani 2 with normal and 3 with special
		addblt->SetFlip(FlipX);
		BulletCount.push_back(addblt);
	}
}

void Bullet::Update(DWORD dt, vector<GameObject*>* coObject)
{
	nx = 0; ny = 0;
	GameObject::Update(dt);
	GameObject::UpdateCollision(coObject);
	if (nx != 0) {
		vx = 0;
	}
	if (ny != 0) {
		vy = 0;
	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<Enemy*>(e->obj)) // if e->obj is Enemies
		{
			Enemy* enemy = dynamic_cast<Enemy*>(e->obj);

			if ((e->nx != 0 || e->ny != 0) && currentAni == 0)
			{
				e->obj->HP_down(damage);
				FlagCollision = true;
				Sound::getInstance()->play("hit", false, 1);
				if (e->obj->GetHP() > 0) e->obj->StartUntouchable();
			}
		}
	}
}

void Bullet::Render()
{
	int center = 1;
	//RenderBoundingBox();
	if (currentAni == 1) center = 2;
	animations[currentAni]->Render(x, y, -1, center, FlipX);
	if (animations[currentAni]->GetCurrentFrame() == 3)
	{
		FlagLimit = true;
	}
}

void Bullet::SetFlip(bool FlipFlag)
{
	FlipX = FlipFlag;
}

void Bullet::SetLimitationByType(int type)
{
	if (type == 3) { limitationX = x + 100.0f; limitationY = y + 0.0f; }//->
	else if (type == 4 || type==7) { limitationX = x - 100.0f; limitationY = y + 0.0f; } //<-
	else if (type == 0) { limitationX = x + 150.0f; limitationY = y + 0.0f; } // ->
	else if (type == 1) { limitationX = x - 150.0f; limitationY = y + 0.0f; } // <-
	else if (type == 2) { limitationX = x + 0.0f; limitationY = y + 150.0f; } // /->
	else if (type == 5) { limitationX = x + 0.0f; limitationY = y - 180.0f; }// \->
}

void HomingMissile::Update(DWORD dt, vector<GameObject*>* coObject)
{
	nx = 0; ny = 0;
	vector<GameObject*> OnlyMap;
	for (UINT i = 0; i < coObject->size()-1; i++)
	{
		if (coObject->at(i)->IsAbletoMove() == false)
			OnlyMap.push_back(coObject->at(i));
	}
	//if (type >= 5)
	//{
		OnlyMap.push_back(coObject->at(coObject->size()-1));
	//}
	//else if (type != 5)
	//{
	//	for (UINT i = 0; i < coObject->size()-2; i++)
	//	{
	//		int a = abs(coObject->at(i)->Get_x() - this->x);
	//		int b = abs(coObject->at(i + 1)->Get_x() - this->x);
	//		if (a < b)
	//		{
	//			IdTarget = coObject->at(i)->GetId();
	//			x_target = coObject->at(i)->Get_x();
	//			y_target = coObject->at(i)->Get_y();
	//		}
	//	}
	//	for (UINT i = 0; i < coObject->size() - 2; i++)
	//	{
	//		if(coObject->at(i))
	//	}
	//}
	GameObject::Update(dt);
	//if (x >= x_target - 8.0f || x <= x_target + 8.0f) vx = 0;
	//if (y >= y_target - 8.0f || y <= y_target + 8.0f) vy = 0;
	GameObject::UpdateCollision(&OnlyMap);
	if ((nx != 0 || ny != 0) && type!=7)
	{
		vx = 0; vy = 0; 
	 FlagCollision = true;
	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if ((dynamic_cast<Enemy*>(e->obj) && type<5) || (dynamic_cast<ControllableChar*>(e->obj))) // if e->obj is Enemies
		{
			if ((e->nx != 0 || e->ny != 0) && currentAni == 0)
			{
				if(e->obj->GetHP()>0)e->obj->HP_down();
				Sound::getInstance()->play("sophiahit", false, 1);
				FlagCollision = true;
				if (e->obj->GetHP() > 0) e->obj->StartUntouchable();
			}
		}
	}
}

//void HomingMissile::Render()
//{
//}

void Enemy_Bomber::Update(DWORD dt, vector<GameObject*>* coOBject, float x_target, float y_target)
{
	Enemy::Update(dt, coOBject);
	wp.Update(dt, coOBject);
	if (x > x_end || x < x_start || nx!=0) vx = -vx;
	if (((x<x_target && x + 60>x_target) || (x > x_target && x - 80 < x_target)) && FlagFire==false && y-60.0f<y_target)
	{
		wp.AddBullet(1, 0, x + 5.0f, y - 10.0f, -0.04f, -0.08f, false, 7);
		vy = +0.03f;
		FlagFire = true;
	}

	if (ny!=0)
	{
		vy = 0.0f; vx = 0.0f;
	}

	if (vx < 0) currentAni = 1; else currentAni = 0;
	if (vy != 0) designatedFrame = 1; else designatedFrame = 0;
}

void Enemy_Floater::Update(DWORD dt, vector<GameObject*>* coOBject, float x_target, float y_target)
{
	Enemy::Update(dt, coOBject);
	wp.Update(dt, coOBject);
	if (nx != 0) vx = -vx;
	if (ny != 0) vy = -vy;
	if ((vx > 0 && x >= x_end) || (x < x_start && vx < 0)) vx = -vx;
	if ((vy < 0 && y <= y_end) || (y > y_start && vy > 0)) vy = -vy;
	CoolDown -= vtCD * dt;
	if (x_start-30.0f < x_target && x_target < x_end && CoolDown <= 0)
	{
		float distance,tempvx,tempvy;
		x > x_target ? distance = x / x_target : distance = x_target / x;
		tempvx = (distance-1)/10;	
		x > x_target ? tempvx = -tempvx : tempvx = tempvx;
		tempvy= vx>0?-vx-0.08f:vx-0.08f;
		wp.AddBullet(1, 0, x+5.0f, y-10.0f, tempvx,tempvy, false, 5);
		wp.SetTarget(x_target, y_target);
		CoolDown = 2000;
	}
	if (vx < 0 && animations.size()>1)	currentAni = 1; else currentAni = 0;
	if (CoolDown >= 1600 && CoolDown<2000) designatedFrame = -1; else designatedFrame = 0;
	//if (nx != 0) vx = -vx;
}

void Enemy_Cannon::Update(DWORD dt, vector<GameObject*>* coOBject)
{
	Enemy::Update(dt, coOBject);
	wp.Update(dt, coOBject);
	CoolDown -= vtCD * dt;
	if (CoolDown <= 2000 && CoolDown>1500)
	{
		if (FlagFired == false)
		{
			wp.AddBullet(1, 1, x + 26.0f, y - 11.0f, 0.3f, 0.0f, false, 3);
			wp.AddBullet(1, 1, x, y - 11.0f, -0.3f, 0.0f, false, 4);
			FlagFired = true;
		}
		designatedFrame = 1;
	}
	else if (CoolDown < 1000 && CoolDown>=500)
	{
		if (FlagFired == false)
		{
			wp.AddBullet(1, 1, x + 11.0f, y, 0.0f, 0.3f, false, 2);
			wp.AddBullet(1, 1, x+11.0, y - 26.0f, 0.0f, -0.3f, false, 5);
			FlagFired = true;
		}
		designatedFrame = 2;
	}
	else if (CoolDown < 500)
	{
		CoolDown = 2500;
	}
	else
	{
		designatedFrame = 0;
		FlagFired = false;
	}
}

ControllableChar::ControllableChar()
{
	status = new STATE; *status = NOTHING;

	Weapon* adddweapon;
	for (int i = 0; i < 4; i++)
	{
		adddweapon = new Weapon();
		WeaponType.push_back(adddweapon);
	}
	HealthPoint = 8;
}

void ControllableChar::Update(DWORD dt, vector<GameObject*> *coObject)
{
	nx = 0, ny = 0;
	vector<GameObject*> ForCollision;
	vector<GameObject*> ForChangeScene;

	ForCollision.clear();
	ForChangeScene.clear();

	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetLayer()== ITEM_LAYER || (coObject->at(i)->GetLayer()>BOSS_DOOR && coObject->at(i)->GetLayer() < LADDER))
			ForCollision.push_back(coObject->at(i));
		else ForChangeScene.push_back(coObject->at(i));
	}
	GameObject::Update(dt,&ForCollision);
	GameObject::UpdateCollision(&ForCollision);
	timerCD -= vtCD * dt;
	timerCS += vtCS * dt;

	if (nx != 0)
	{
		vx = 0;
	}
	if (ny != 0)
	{
		vy = 0;
		IsFalling = false;
		if (*status == JUMPING) *status = NOTHING;
	}

	//invincible time
	if (GetTickCount() - untouchable_start > 1000)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	//Collision logic with enemies
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<Enemy*>(e->obj)) // if e->obj is Enemies
		{
			if ((e->nx != 0 || e->ny != 0) && untouchable == 0)
			{
				if (HealthPoint > 0) HealthPoint--;
				if (HealthPoint == 0) y += 23.0f;
				StartUntouchable();
				Sound::getInstance()->play("sophiahit", false, 1);
			}
		}

		if (dynamic_cast<Item*>(e->obj)) // if e->obj is Items
		{
			Item* item = dynamic_cast<Item*>(e->obj);
			if ((e->nx != 0 || e->ny != 0) && e->obj->GetHP() > 0)
			{
				if (item->GetId() == 50000)
				{
					if (HealthPoint < 8)
					{
						HealthPoint++;
					}
				}
				if (item->GetId() == 50001)
				{
					Upgrade_BulletImage(754);
				}
				e->obj->HP_down();
				Sound::getInstance()->play("itemtaken", false, 1);
				item->SetDropItemState(PICKED);
			}
		}
	}
	if (untouchable != 0) RenderColor = 0; else RenderColor = 255;

	if (x > 2048) x = 0;
	else if (x < 0) x = 2032;
	if (y < 0) y = 2048;
	else if (y > 2048) y = 0;

	if (FlagAutomatic == false && FlagBossFight==false)
		for (int i = 0; i < ForChangeScene.size(); i++)
		{
			if (ForChangeScene[i]->GetLayer() == LADDER)
			{
				if (ForChangeScene[i]->GetBoundingBox()->IsContainWorld(this->GetBoundingBox()))
					FlagClimbing = true;
				else FlagClimbing = false;
			}
			else if (ForChangeScene[i]->GetBoundingBox()->IsContainWorld(this->GetBoundingBox()))
			{
				if (ForChangeScene[i]->GetLayer() != TRAP)
				{
					FlagAutomatic = true;
					vtCS = 0.5f;
					if (ForChangeScene[i]->GetLayer() == BOSS_DOOR) ThatTheOne = true;
				}
				else if (untouchable == 0)
				{
					if (HealthPoint > 0) HealthPoint--;
					if (HealthPoint == 0) y += 23.0f;
					StartUntouchable();
					Sound::getInstance()->play("sophiahit", false, 1);
				}
			}
		}
	else
	{
		if (timerCS > timeCSlimit)
		{
			FlagAutomatic = false;
			timerCS = 0;
			vtCS = 0;
			if (ThatTheOne == true)
			{
				FlagBossFight = true;
				ThatTheOne = false;
			}
		}
	}
}

void ControllableChar::UpdateWeapon(DWORD dt,vector<GameObject*> *coObject)
{
	WeaponType[curWeapon]->Update(dt,coObject);
}

void ControllableChar::RenderWeapon()
{
	//if (curWeapon == 0)
	//{
		WeaponType[curWeapon]->Render();
	//}
}

void ControllableChar::ResetLife()
{
		currentAni = lastAni = 0;
		HealthPoint = 8;
}

void ControllableChar::Add_BulletImage(int id,int weapontype)
{
	WeaponType[weapontype]->AddBulletId(id);
}

void ControllableChar::Upgrade_BulletImage(int id)
{
	WeaponType[0]->UpgradeBulletId(id);
}


bool ControllableChar::LockCam(float x, float y)
{
	if ((x > 512 && x < 1024 && y>1776)
		|| (x > 1024 && x < 2048 && y < 1008 && y>752)
		|| (x > 1024 && x < 1536 && y < 1776 && y>1520))
		return true;
	return false;
}

void Enemy_With_Weapon::CreateSprite()
{
		wp.AddBulletId(753);
		wp.AddBulletId(751);
}
