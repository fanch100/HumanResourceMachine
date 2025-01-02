#include "main.hpp"



GameStopButton::GameStopButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
GameStopButton::~GameStopButton() = default;
void GameStopButton::OnClick()
{
    cur_level->QuitGame();
    cur_level->InitGame();
    game_scene.game_result = 0;
}
