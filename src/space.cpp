#include "main.hpp"
Space::Space(RECT pos, int color, int value)
{
    position = pos;
    this->value = value;
}
Space::~Space() = default;
void Space::Draw(int color)
{
    // setlinecolor(color);
    // setfillcolor(color);
    putimage_alpha(position.left, position.top, &img_space);
    settextcolor(color);//设置字体颜色
    settextstyle(10, 10, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    // drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
    drawtext(_T(std::to_string(value).c_str()), &position, DT_CENTER);
    if (this->block != nullptr) {
        std :: cout << "value: " << value << std :: endl;
        std :: cout << "Draw block: " << std::endl;
        this->block->Draw(color);
    }
}
void Space::SetValue(int value)
{
    this->value = value;
}
void Space::SetBlock(Block* block)
{
    this->block = block;
}
int Space::GetValue()
{
    return this->value;
}
Block* Space::GetBlock()
{
    return this->block;
}
RECT Space::GetPosition()
{
    return this->position;
}