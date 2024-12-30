#include "main.hpp"
StartButton::StartButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
StartButton::~StartButton() = default;
void StartButton::OnClick()
{
    game_stage = GameStage::LevelSelect;
    scene_manager.ChangeScene(SceneManager::GameScene::LevelSelect);
}