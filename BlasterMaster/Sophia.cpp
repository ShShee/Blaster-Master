#include "Sophia.h"

Sophia::Sophia(float x, float y/*, float vx, float vy*/)
{
	GameObject::SetPos(x,y);
	this->core = new Core();
	this->core->SetPos(x, y);
	this->tire1 = new Tire();
	this->tire1->SetPos(x - 10.0f, y + 4.0f);
	this->tire2 = new Tire();
	this->tire2->SetPos(x + 10.0f, y + 4.0f);
	this->body = new Body();
	this->body->SetPos(x - 10.0f, y - 4.0f);
	this->turret = new Turret();
	this->turret->SetPos(x + 10.0f, y - 4.0f);
	//this->vx = vx;
	//this->vy = vy;
}

void Sophia::SetSpeed(float vx, float vy)
{
	this->core->SetSpeed(vx, vy);
	this->tire1->SetSpeed(vx, vy);
	this->tire2->SetSpeed(vx, vy);
	this->body->SetSpeed(vx, vy);
	this->turret->SetSpeed(vx, vy);
}

void Sophia::Update(DWORD dt)
{

}

void Sophia::Add_Image(int idCore, int idTire1,int idTire2, int idBody, int idTurret)
{
	if (idCore != 0) core->Add_Image(idCore);
	if (idTire1 != 0) tire1->Add_Image(idTire1);
	if (idTire2 != 0) tire2->Add_Image(idTire2);
	if (idBody != 0) body->Add_Image(idBody);
	if (idTurret != 0) turret->Add_Image(idTurret);
}

void Sophia::Render()
{
	this->core->Render();
	this->tire1->Render();
	this->tire2->Render();
	this->body->Render();
	this->turret->Render();
}

void Core::Update(DWORD dt)
{

}

void Core::Render()
{
	animations[currentAni]->Render(x, y, designatedFrame);
}

void Tire::Update(DWORD dt)
{
}

void Tire::Render()
{
	animations[currentAni]->Render(x, y, designatedFrame);
}
void Turret::Update(DWORD dt)
{
}

void Turret::Render()
{
	animations[currentAni]->Render(x, y, designatedFrame);
}

void Body::Update(DWORD dt)
{
}

void Body::Render()
{
	animations[currentAni]->Render(x, y, designatedFrame);
}


