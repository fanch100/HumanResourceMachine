#include "main.hpp"

TextBox::TextBox() = default;
void TextBox::Init(RECT pos, int mxlen)
{
    this->maxlen = mxlen;
    this->text = new TCHAR[maxlen];
    text[0] = 0;
    this->position = pos;
}
TextBox::~TextBox()
{
    if (text != nullptr)
    {
        delete[] text;
        text = nullptr;
    }
}
TCHAR* TextBox::GetText()
{
    return text;
}

bool TextBox::CheckCursorInTextBox(int x, int y)//判断光标是否在按钮上
{
    return position.left <= x && x <= position.right && position.top <= y && y <= position.bottom;
}

// 绘制界面
// void Draw()
// {
//     // 备份环境值
//     int oldlinecolor = getlinecolor();
//     int oldbkcolor = getbkcolor();
//     int oldfillcolor = getfillcolor();

//     setlinecolor(LIGHTGRAY);        // 设置画线颜色
//     setbkcolor(0xeeeeee);             // 设置背景颜色
//     setfillcolor(0xeeeeee);             // 设置填充颜色
//     fillrectangle(position.left, position.top, position.right, position.bottom);
//     outtextxy(position.left + 10, position.top + 5, text);

//     // 恢复环境值
//     setlinecolor(oldlinecolor);
//     setbkcolor(oldbkcolor);
//     setfillcolor(oldfillcolor);
// }
void TextBox::Draw()
{
    std:: cout << "left = " << position.left << std::endl;
    std:: cout << "top = " << position.top << std::endl;
    std:: cout << "right = " << position.right << std::endl;
    std:: cout << "bottom = " << position.bottom << std::endl;
    setlinecolor(LIGHTGRAY); 
    setbkcolor(0xeeeeee);       
    setfillcolor(0xeeeeee);             
    fillrectangle(position.left, position.top, position.right, position.bottom);
    outtextxy(position.left + 10, position.top + 5, text);
}

void TextBox::ProcessMessage(const ExMessage &msg)
{
    // std :: cout << "TextBox::ProcessMessage" << std::endl;
    setlinecolor(BLACK);          
    setbkcolor(WHITE);              
    setfillcolor(WHITE);                
    fillrectangle(position.left, position.top, position.right, position.bottom);
    outtextxy(position.left + 10, position.top + 5, text);

    int width = textwidth(text);    // 字符串总宽度
    if (msg.message == WM_LBUTTONDOWN)
    {
        if (CheckCursorInTextBox(msg.x,msg.y)) is_input = true;// 鼠标点击文本框内，开始文本输入
        else if (!CheckCursorInTextBox(msg.x,msg.y)) is_input = false;
    }
    else if (msg.message == WM_CHAR && is_input == true)
    {
        size_t len = _tcslen(text);
        switch (msg.ch)
        {
        case '\b':                // 用户按退格键，删掉一个字符
            if (len > 0)
            {
                text[len - 1] = 0;
                width = textwidth(text);
                clearrectangle(position.left + 10 + width, position.top + 1, position.right - 1, position.bottom - 1);
            }
            break;
        case '\r':                // 用户按回车键，结束文本输入
        case '\n':
            is_input = false;
            std :: cout << "Text=\"" << text  << '\"'<< std :: endl;
            break;
        default:                // 用户按其它键，接受文本输入
            if (len < maxlen - 1)
            {
                text[len++] = msg.ch;
                text[len] = 0;

                clearrectangle(position.left + 10 + width + 1, position.top + 3, position.left + 10 + width + 1, position.bottom - 3);    // 清除画的光标
                width = textwidth(text);                // 重新计算文本框宽度
                outtextxy(position.left + 10, position.top + 5, text);        // 输出新的字符串
            }
        }
    }
}