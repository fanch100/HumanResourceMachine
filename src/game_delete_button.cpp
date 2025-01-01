#include "main.hpp"



GameInputButton::GameInputButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
GameInputButton::~GameInputButton() = default;
void GameInputButton::OnClick()
{
    std :: cout << "GameInputButton::OnClick()" << std :: endl;
    game_scene.InputUpdate();
}
