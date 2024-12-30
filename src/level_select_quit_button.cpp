#include "main.hpp"



LevelSelectQuitButton::LevelSelectQuitButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
LevelSelectQuitButton::~LevelSelectQuitButton() = default;
void LevelSelectQuitButton::OnClick()
{
    scene_manager.ChangeScene(SceneManager::GameScene::Menu);
}
