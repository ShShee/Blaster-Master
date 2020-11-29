#pragma once
#include <Windows.h>
#include <vector>
#include "GameObject.h"

#define MAX_LEVEL 4

class Quadtree
{
private:
	int level;
	BoundingBox* region;
	int max_object;
	vector<GameObject*>ListObject;
	/*vector<GameObject*>ListObjectOnCurCam;*/
	Quadtree** nodes;

	bool IsContain(BoundingBox* bx);
	void Split();

public:
	Quadtree(int level, BoundingBox* region,int max_object=40);
	void Clear();
	void Insert(GameObject* gobj);
	void Retrieve(vector<GameObject*> return_ListObject,GameObject* gobj);
	void GetListObjectinCamera(vector<GameObject*> &return_ListObject, BoundingBox* camera);
	void Render();
	int GetNumObj() { return this->ListObject.size(); }
	
	/*vector<GameObject*> GetListObjectOnCurCam();*/
};

