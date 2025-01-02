#include "main.hpp"



GameFileInputButton::GameFileInputButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
GameFileInputButton::~GameFileInputButton() = default;
void GameFileInputButton::OnClick()
{
    game_scene.FileInputUpdate();
}
