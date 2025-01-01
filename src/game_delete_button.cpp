#include "main.hpp"



GameDeleteButton::GameDeleteButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
GameDeleteButton::~GameDeleteButton() = default;
void GameDeleteButton::OnClick()
{
    game_scene.DeleteUpdate();
}
