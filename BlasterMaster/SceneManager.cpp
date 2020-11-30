#include "SceneManager.h"

SceneManager* SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
    Life = new CAnimation(100);

    Scene* addScene;
    addScene = new MainAreaScene();
    ListScene.push_back(addScene);

    addScene = new OverWorldScene();
    ListScene.push_back(addScene);

    addScene = new EndingScene();
    ListScene.push_back(addScene);

    addScene = new OpeningScene();
    ListScene.push_back(addScene);
}

SceneManager* SceneManager::GetInstance()
{
    if (_instance == NULL) _instance = new SceneManager();
    return _instance;
}

Scene* SceneManager::GetCurrentScene()
{
    return ListScene[currentScene];
}

KeyEventHandler* SceneManager::GetKeyEventHandler()
{
    return ListScene[currentScene]->GetKeyEventHandler();
}

void SceneManager::LoadContent()
{
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/jump.wav", "jump");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/sophiahit.wav", "sophiahit");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/fire.wav", "fire");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/hit.wav", "hit");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/itemtaken.wav", "itemtaken");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/explode.wav", "explode");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/stage1.wav", "stage1");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/opening.wav", "opening");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/endingscene.wav", "endingscene");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/explode.wav", "explode");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/runin.wav", "runin");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/bossfight.wav", "bossfight");
    Sound::getInstance()->loadSound("SpritesSource/Soundtrack/collaspe.wav", "collapse");
    for(UINT i=0;i<ListScene.size();i++)
    ListScene[i]->LoadContent();

    CTextures::GetInstance()->Add(ID_TEX_LIFE, L"SpritesSource\\LifeCount.png", D3DCOLOR_XRGB(54, 115, 1));
    LPDIRECT3DTEXTURE9 texLife = CTextures::GetInstance()->Get(ID_TEX_LIFE);
    CSprites* sprites = CSprites::GetInstance();
    sprites->Add(95051, 0, 0, 300, 300, texLife);
    sprites->Add(95052, 391, 0, 691, 300, texLife);
    sprites->Add(95053, 0, 320, 300, 620, texLife);
    
    Life->Add(95053);
    Life->Add(95052);
    Life->Add(95051);
    
}

void SceneManager::Update(DWORD dt)
{
    timer -= vt * dt;
    if (timer <= 0 || currentScene == 3)
    {
        if (ListScene[currentScene]->GetFlagChangeScene() == true)
        {
            ListScene[currentScene]->SetFlageChangeScene(false);
            if (ListScene[currentScene]->HasBossorNot() == false)
            {
                if (currentScene == 0)
                {
                    ListScene[1]->SetGate(ListScene[0]->GetGate());
                    currentScene = 1;
                }
                else
                {
                    if (currentScene == 3) vt = 0.5f;
                    currentScene = 0;
                }
            }
            else currentScene = 2;
            CGame::GetInstance()->InitKeyBoard(ListScene[currentScene]->GetKeyEventHandler());
        }
        if (ListScene[currentScene]->HasBeenDeadYet() == true)
        {
            lifeCount == 0 ? lifeCount = 2 : lifeCount--;
            timer = 1000;  
        }
        ListScene[currentScene]->Update(dt);
    }
    else
    {
        CGame::GetInstance()->SetCamPos(300.0f, 300.0f);
    }
    switch (currentScene)
    {
    case 2:
        Sound::getInstance()->stop("bossfight");
        break;
    case 0:
        Sound::getInstance()->play("stage1", true, 0);
        Sound::getInstance()->stop("runin");
        break;
    }
}

void SceneManager::Render()
{
    if (timer > 0 && (currentScene == 1 || currentScene == 0))
    {
        Life->Render(300.0f, 300.0f /*+ 48.0f*/, lifeCount);
    }
    else
    ListScene[currentScene]->Render();
}
