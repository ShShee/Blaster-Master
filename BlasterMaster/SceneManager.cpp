#include "SceneManager.h"

SceneManager* SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
    Scene* addScene;
    addScene = new MainAreaScene();
    ListScene.push_back(addScene);

    addScene = new OverWorldScene();
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
    for(UINT i=0;i<ListScene.size();i++)
    ListScene[i]->LoadContent();
}

void SceneManager::Update(DWORD dt)
{
    if (ListScene[currentScene]->GetFlagChangeScene() == true)
    {
        ListScene[currentScene]->SetFlageChangeScene(false);
        currentScene == 0 ? currentScene = 1 : currentScene = 0;
        CGame::GetInstance()->InitKeyBoard(ListScene[currentScene]->GetKeyEventHandler());
    }
    ListScene[currentScene]->Update(dt);
}

void SceneManager::Render()
{
    ListScene[currentScene]->Render();
}
