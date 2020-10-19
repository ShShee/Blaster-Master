#pragma once
#include "JasonOW.h"
class Jason: public JasonOW
{
private:
	static Jason* _instance;
public:
	Jason() :JasonOW() {}
	void Update(DWORD dt);
	void Render();
	void SetAni(int ani);
	static Jason* GetInstance();
};

