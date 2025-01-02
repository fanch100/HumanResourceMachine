#include "main.hpp"



GamePlayButton::GamePlayButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
GamePlayButton::~GamePlayButton() = default;
void GamePlayButton::OnClick()
{
    game_scene.Update();
}
