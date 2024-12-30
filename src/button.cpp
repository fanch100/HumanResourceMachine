#include "main.hpp"


Button::Button(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed)
{
    position = pos;
    loadimage(&btn_default, path_btn_default);
    loadimage(&btn_hovered, path_btn_hovered);
    loadimage(&btn_pushed, path_btn_pushed);
}
Button::~Button() = default;
void Button::Draw(LPCTSTR str)
{
    switch (stage)
    {
        case Stage::Default:
            putimage(position.left, position.top, &img_btn_default);
            break;
        case Stage::Hovered:
            putimage(position.left, position.top, &img_btn_hovered);
            break;
        case Stage::Pushed:
            putimage(position.left, position.top, &img_btn_pushed);
            break;
    }

    settextstyle(20, 0, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    drawtext(str, &(this->position), DT_CENTER);
}
void Button::ProcessMessage(const ExMessage &msg)
{
    switch (msg.message)
    {
        case WM_MOUSEMOVE:
            if (stage == Stage::Default && CheckCursorInButton(msg.x, msg.y))
                stage = Stage::Hovered;
            else if (stage == Stage::Hovered && !CheckCursorInButton(msg.x, msg.y))
                stage = Stage::Default;
            break;
        case WM_LBUTTONDOWN:
            if (stage == Stage::Hovered)
                stage = Stage::Pushed;
            break;
        case WM_LBUTTONUP:
            if (stage == Stage::Pushed)
            {
                OnClick();
                stage = Stage::Hovered;
            }
            break;
        default:
            break;
    }
}
bool Button::CheckCursorInButton(int x, int y)//判断光标是否在按钮上
{
    return position.left <= x && x <= position.right && position.top <= y && y <= position.bottom;
}