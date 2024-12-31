#include "main.hpp"
Block::Block(RECT pos, int color, int value)
{
    position = pos;
    this->value = value;
}
Block::Block(const Block& block)
{
    position = block.position;
    value = block.value;
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
bool Block::Move(int x, int y)
{
    int delta_x = x - position.left;
    int delta_y = y - position.top;
    double dis = std::sqrt(delta_x * delta_x + delta_y * delta_y);
    int final_x = x, final_y = y;
    if (fabs(dis) > eps)
    {
        int normalize_x = (int)(delta_x * move_speed / dis);
        int normalize_y = (int)(delta_y * move_speed / dis);
        final_x = normalize_x + position.left;
        final_y = normalize_y + position.top;
        if (dis < std::sqrt(normalize_x * normalize_x + normalize_y * normalize_y))
        {
            final_x = x;
            final_y = y;
        }
        position = {final_x, final_y, final_x + block_width, final_y + block_height};
    }
    return (final_x==x) && (final_y == y);
}
void Block::SetValue(int value)
{
    this->value = value;
}
int Block::GetValue()
{
    return this->value;
}