#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"
#include "Sound.h"
class Scene
{
protected:
    bool FlagChangeScene = false;
    int Gate=0;
public:
    Scene();
    virtual void Update(DWORD dt);
    virtual void LoadContent();
    virtual void Render();

    virtual KeyEventHandler* GetKeyEventHandler()=0;
    bool GetFlagChangeScene() { return this->FlagChangeScene; }
    void SetFlageChangeScene(bool fcs) { this->FlagChangeScene = fcs; }
    int GetGate() { return this->Gate; }

};

