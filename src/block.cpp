#include "block.hpp"
Block::Block(RECT pos, int color, LPCTSTR path_block, int value)
{
    position = pos;
    this->value = value;
    loadimage(&img, path_block);
}
Block::~Block() = default;
void Block::Draw(int color)
{
    // setlinecolor(color);
    // setfillcolor(color);
    putimage_alpha(position.left, position.top, &img_block);
    settextcolor(color);//设置字体颜色
    settextstyle(20, 0, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    // drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
    drawtext(_T(std::to_string(value).c_str()), &position, DT_CENTER);
}
void Block::Move(int x, int y)
{
    int delta_x = x - position.left;
    int delta_y = y - position.top;
    double dis = std::sqrt(delta_x * delta_x + delta_y * delta_y);
    if (fabs(dis) > eps)
    {
        int final_x = (int)(delta_x * move_speed / dis) + position.left;
        int final_y = (int)(delta_y * move_speed / dis) + position.top;
        position = {final_x, final_y, final_x + block_width, final_y + block_height};
    }
}
void Block::SetValue(int value)
{
    this->value = value;
}
int Block::GetValue()
{
    return this->value;
}