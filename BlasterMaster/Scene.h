#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"
#include "Sound.h"
#include "GameObject.h"
#include "Textures.h"
#include "Enemies.h"
#include "WorldMap.h"
#include "Quadtree.h"
#include "Item.h"
#include "MainPlayer.h"

class Scene
{
protected:
    bool FlagChangeScene = false;
    int Gate=0;
    bool HasBoss=false;

    KeyEventHandler* keyHandler;
public:
    Scene();
    virtual void Update(DWORD dt);
    virtual void LoadContent();
    virtual void Render();

    KeyEventHandler* GetKeyEventHandler() { return this->keyHandler; }
    bool GetFlagChangeScene() { return this->FlagChangeScene; }
    void SetFlageChangeScene(bool fcs) { this->FlagChangeScene = fcs; }
    int GetGate() { return this->Gate; }
    void SetGate(int gate) { this->Gate = gate; }
    virtual bool HasBossorNot() { return HasBoss; }
    virtual bool HasBeenDeadYet() { return false; }
};

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

