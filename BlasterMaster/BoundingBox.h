#pragma once
#include "Game.h"
class BoundingBox
{
public:
	float x;
	float y;
	int width;
	int height;

	BoundingBox(float x=0, float y=0, int width=0, int height=0);
	bool IsContain(BoundingBox *bx);

};

