#include "Quadtree.h"

Quadtree::Quadtree(int level, BoundingBox* region)
{
    this->level = level;
    this->region = region;
}

bool Quadtree::IsContain(BoundingBox* bx)
{
    return region->IsContain(bx);
}

void Quadtree::Split()
{
    nodes = new Quadtree * [4];
    int width = region->width / 2;
    int height = region->height / 2;
    float pos_X;
    float pos_Y;

    //nodes[0] = new Quadtree(level + 1,new BoundingBox(region->x, region->y,width,height));
    //nodes[1] = new Quadtree(level + 1,new BoundingBox(region->x + region->width / 2, region->y,width,height));
    //nodes[2] = new Quadtree(level + 1,new BoundingBox(region->x, region->y + region->height / 2,width,height));
    //nodes[3] = new Quadtree(level + 1,new BoundingBox(region->x + region->width / 2,region->y + region->height / 2,width,height));

    for (int i = 0; i < 4; i++)
    {
        if (i % 2 == 0) pos_X = region->x;  else pos_X = region->x + region->width / 2;
        if (i < 2)      pos_Y = region->y; else pos_Y = region->y + region->height / 2;
        nodes[i] = new Quadtree(level+1, new BoundingBox(pos_X, pos_Y, width, height));
    }
}

//Quadtree* CreateQuadTree()
//{
//    Quadtree* quadtree = new Quadtree(1, new BoundingBox(0, 0, 2048, 2048));
//    return quadtree;
//
//}

void Quadtree::Clear()
{
    if (nodes)
    {
        for (int i = 0; i < 4; i++)
        {
            nodes[i]->Clear();
            delete nodes[i];
        }
        delete[] nodes;
    }

    ListObject.clear();

    for (size_t i = 0; i < (size_t)ListObject.size(); i++)
    {
        delete ListObject[i];
    }

    delete region;
}

void Quadtree::Insert(GameObject* gobj)
{
    BoundingBox* bx = gobj->GetBoundingBox();
    if (nodes)
    {
        for (int i = 0; i < 4; i++)
            if (nodes[i]->IsContain(bx))  nodes[i]->Insert(gobj);
        OutputDebugStringW(L"Done adding to quadtree\n");
        return;
    }

    if (this->IsContain(bx))   ListObject.push_back(gobj);

    if (ListObject.size() > MAX_OBJECT_IN_REGION && level < MAX_LEVEL)
    {
        Split();
        
        while (!ListObject.empty())
        {
            bx = ListObject.back()->GetBoundingBox();
            for (int i = 0; i < 4; i++)
                if (nodes[i]->IsContain(bx))
                {
                    nodes[i]->Insert(ListObject.back());
                }  
            ListObject.pop_back();
        }
    }
}

void Quadtree::Retrieve(vector<GameObject*> return_ListObject,GameObject* gobj)
{
    BoundingBox* bx = gobj->GetBoundingBox();
    if (nodes)
    {
        for (int i = 0; i < 4; i++)
            if (nodes[i]->IsContain(bx))  nodes[i]->Retrieve(return_ListObject, gobj);
       
        return ;
    }
    if (this->IsContain(bx))
    {
        for (GameObject* obj:ListObject)
        {
            if (gobj != obj)
                return_ListObject.push_back(obj);
        }
    }
}

void Quadtree::GetListObjectinCamera(vector<GameObject*> &return_ListObject, BoundingBox* camera)
{
    if (nodes)
    {
        for (int i = 0; i < 4; i++)
            if (nodes[i]->IsContain(camera))  nodes[i]->GetListObjectinCamera(return_ListObject, camera);

        return;
    }
    if (this->IsContain(camera))
    {
        for (GameObject* obj : ListObject)
        {
                return_ListObject.push_back(obj);
        }
    }
}

//void Quadtree::Render()
//{
//    if (nodes)
//    {
//        for (int i = 0; i < 4; i++)
//           nodes[i]->Render();
//
//        return;
//    }
//    if (ListObject.size()!=0)
//    {
//        for (GameObject* obj : ListObject)
//        {
//            obj->Render();
//        }
//    }
//}

//vector<GameObject*> Quadtree::GetListObjectOnCurCam()
//{
//    return vector<GameObject*>();
//}
