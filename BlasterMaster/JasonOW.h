#pragma once
#include "GameObject.h"


class JasonOW : public MovingObject
{
private:
	static JasonOW* _instance;
protected:
	int lastAni = 0;
	STATE* status;
public:
	JasonOW() {status = new STATE; *status = NOTHING;
	}
	void Update(DWORD dt);
	void Render();
	void SetAni(int ani);
	static JasonOW* GetInstance();
};

