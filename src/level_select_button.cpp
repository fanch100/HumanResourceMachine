#include "main.hpp"


LevelSelectButton::LevelSelectButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed, int val) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed),value(val){ }
LevelSelectButton::~LevelSelectButton() = default;

void LevelSelectButton::OnClick()
{
    game_stage = GameStage::Game;
    cur_level = &level_list[value - 1];
    level_value = this->value;
    cur_level->InitGame();
}