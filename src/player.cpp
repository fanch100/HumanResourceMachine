#include "main.hpp"


Player::Player(RECT pos)
{
    position = pos;
}
Player::~Player() = default;
void Player::Draw()
{
    // setlinecolor(color);
    // setfillcolor(color);
    putimage_alpha(position.left, position.top, &img_player);
    // settextcolor(color);//设置字体颜色
    // settextstyle(20, 0, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    // drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
    // drawtext(_T(std::to_string(value).c_str()), &position, DT_CENTER);
}
Block* Player::GetBlock()
{
    return block;
}
void Player::SetBlock(Block* block)
{
    this->block = block;
}
void Player::SetPosition(RECT pos)
{
    this->position = pos;
}
RECT Player::GetPosition()
{
    return position;
}
