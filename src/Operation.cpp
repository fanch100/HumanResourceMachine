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
    std::string str;
    if (type == 1 || type == 2) str = operation_number_to_name[type];
    else str = operation_number_to_name[type] + " " + std::to_string(value);
    drawtext(_T(str.c_str()), &position, DT_CENTER);
}

void Operation::DrawTriangle()
{
    setfillcolor(GREEN);
    POINT points[] = {{position.left-20, position.top}, {position.left-20, position.bottom}, {position.left, (position.top+position.bottom)/2}};
    fillpolygon(points, 3);
}

int Operation::GetValue()
{
    return value;
}
int Operation::GetType()
{
    return type;
}