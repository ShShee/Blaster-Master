#include "BoundingBox.h"

BoundingBox::BoundingBox(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool BoundingBox::IsContain(BoundingBox* bx)
{
	return !(bx->x+bx->width < this->x ||
		bx->height+bx->y < this->y ||
		bx->x > this->width + this->x ||
		bx->y > this->height+ this->y);
}
