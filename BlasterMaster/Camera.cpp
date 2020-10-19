#include "Camera.h"

void Camera::SetCamPos(float x, float y)
{
	if (x <= 0) cam_x = 0;
	else if (x >= 1763) cam_x = 1763;
	else cam_x = x;
	if (y <= 0) cam_y = +0;
	else if (y >= 1786) cam_y = 1786;
	else cam_y = y;
}
