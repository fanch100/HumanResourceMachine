#include "main.hpp"
Block::Block(RECT pos, int color, int value)
{
    position = pos;
    this->value = value;
}
Block& Block::operator= (const Block& block)
{
    this->position = block.position;
    this->value = block.value;
    this->is_hiding = block.is_hiding;
    return *this;
}
Block::Block(const Block& block)
{
    *this = block;
}
Block::~Block() = default;
void Block::Draw(int color)
{
    std :: cout << "is_hiding:" << is_hiding << std :: endl;
    if (is_hiding == true) return;
    
    // setlinecolor(color);
    // setfillcolor(color);
    putimage_alpha(position.left, position.top, &img_block);
    settextcolor(color);//设置字体颜色
    settextstyle(20, 0, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    // drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
    drawtext(_T(std::to_string(value).c_str()), &position, DT_CENTER);
}
void Block::SetValue(int value)
{
    this->value = value;
}
int Block::GetValue()
{
    return this->value;
}

RECT Block::GetPosition()
{
    return this->position;
}
void Block::SetPosition(RECT pos)
{
    this->position = pos;
}