#include "main.hpp"
Operation::Operation(RECT pos, int value, int type)
{
    position = pos;
    this->value = value;
    this->type = type;
}
Operation::~Operation() = default;
void Operation::Draw(int color)
{
    // setlinecolor(color);
    setfillcolor(WHITE);
    fillrectangle(position.left, position.top, position.right, position.bottom);
    settextcolor(color);//设置字体颜色
    settextstyle(20, 0, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    // drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
    drawtext(_T(operation_number_to_name[value].c_str()), &position, DT_CENTER);
}