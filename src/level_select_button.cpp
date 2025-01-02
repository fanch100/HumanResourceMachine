#include "main.hpp"


LevelSelectButton::LevelSelectButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed, int val) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed),value(val){ }
LevelSelectButton::~LevelSelectButton() = default;

void LevelSelectButton::OnClick()
{
    game_stage = GameStage::Game;
    cur_level = &level_list[value - 1];
    level_value = this->value;
    
    scene_manager.ChangeScene(SceneManager::GameScene::Game);
}

void LevelSelectButton::Draw(LPCTSTR str)
{
    switch (stage)
    {
        case Stage::Default:
            putimage_alpha(position.left, position.top, &btn_default);
            break;
        case Stage::Hovered:
            putimage_alpha(position.left, position.top, &btn_hovered);
            break;
        case Stage::Pushed:
            putimage_alpha(position.left, position.top, &btn_pushed);
            break;
    }
    if(level_list[value - 1].is_completed == true)
    {
        putimage_alpha(position.left, position.top - button_height, &img_level_complete);
    }
    settextstyle(20, 0, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    drawtext(str, &(this->position), DT_CENTER);
}