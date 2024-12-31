#include "main.hpp"

SceneManager::SceneManager() = default;
SceneManager::~SceneManager() = default;
void SceneManager::Update()
{
    return current_scene->Update();
}
void SceneManager::Draw()
{
    return current_scene->Draw();
}
void SceneManager::ProcessMessage(const ExMessage &msg)
{
    std:: cout<< "SceneManager::ProcessMessage" << std::endl;
    return current_scene->ProcessMessage(msg);
}
void SceneManager::ChangeScene(GameScene type)
{
    current_scene->Quit();
    switch (type)
    {
        case GameScene::Menu:
            current_scene = &menu_scene;
            break;
        case GameScene::LevelSelect:
            current_scene = &level_select_scene;
            break;
        case GameScene::Game:
            current_scene = &game_scene;
            break;
    }
    current_scene->Init();
}
void SceneManager::SetScene(Scene *scene)
{
    current_scene = scene;
    current_scene->Init();
}
//Scene* SceneManager::GetCurrentScene(){return (Scene*)nullptr;};