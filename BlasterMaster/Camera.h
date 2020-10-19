#pragma once
class Camera
{
	float cam_x=0.0f;
	float cam_y=0.0f;
public:
	float get_x() { return this->cam_x; }
	float get_y() { return this->cam_y; }
	void SetCamPos(float x, float y);
};

