#include "main.hpp"



GameQuitButton::GameQuitButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
GameQuitButton::~GameQuitButton() = default;
void GameQuitButton::OnClick()
{
    scene_manager.ChangeScene(SceneManager::GameScene::LevelSelect);
}
