#include "main.hpp"


Slider::Slider(RECT pos, LPCTSTR str)
{
    position = pos;
    cur_x = pos.left;
    cur_y = pos.top;
    stage = Stage::Default;
    this->str = str;
}
Slider::~Slider() = default;
void Slider::Draw()
{
    setfillcolor(RGB(45, 45, 45));
    solidrectangle(position.left+3, position.top+3, position.right+3, position.bottom+3);
    setfillcolor(BLUE);
    solidrectangle(position.left, position.top, position.right, position.bottom);
    settextstyle(20, 0, _T("monospace"));//设置字体
    //outtextxy(position.left+10, position.top+40, str);//输出文字
    drawtext(this->str, &position, DT_CENTER);
}
void Slider::ProcessMessage(const ExMessage &msg)
{
    // switch (msg.message)
    // {
    // 	case WM_MOUSEMOVE:
    // 		if (stage == Stage::Default && CheckCursorInSlider(msg.x, msg.y))
    // 			stage = Stage::Hovered;
    // 		else if (stage == Stage::Hovered && !CheckCursorInSlider(msg.x, msg.y))
    // 			stage = Stage::Pushed;
    // 		// else if (stage == Stage::Default)
    // 		// {
    // 		// 	int delta_x = msg.x - cur_x;
    // 		// 	int delta_y = msg.y - cur_y;
    // 		// 	position = {position.left + delta_x, position.top + delta_y, position.right + delta_x, position.bottom + delta_y};
    // 		// 	std::cout << "msg:x: " << msg.x << " y: " << msg.y << std::endl;
    // 		// 	std::cout << "cur:x: " << cur_x << " y: " << cur_y << std::endl;
    // 		// 	std::cout << "delta:x: " << delta_x << " y: " << delta_y << std::endl;
    // 		// 	cur_x = msg.x;
    // 		// 	cur_y = msg.y;
    // 		// }
    // 		break;
    // 	case WM_LBUTTONDOWN:
    // 		if (stage == Stage::Hovered)
    // 		{
    // 			stage = Stage::Pushed;	
    // 			cur_x = msg.x;
    // 			cur_y = msg.y;
    // 		}
    // 		break;
    // 	// case WM_LBUTTONUP:
    // 	// 	if (stage == Stage::Pushed)
    // 	// 		OnClick();
    // 	// 	break;
    // 	default:
    // 		break;
    // }
    switch (msg.message)
    {
        case WM_MOUSEMOVE:
            if (stage == Stage::Pushed)
            {
                int delta_x = msg.x - cur_x;
                int delta_y = msg.y - cur_y;
                position = {position.left + delta_x, position.top + delta_y, position.right + delta_x, position.bottom + delta_y};
                cur_x = msg.x;
                cur_y = msg.y;
                // 确保滑块不会超出窗口边界
                if (position.left < 0) position.left = 0;
                if (position.top < 0) position.top = 0;
                if (position.right > window_width) position.right = window_width;
                if (position.bottom > window_height) position.bottom = window_height;
                position.right = position.left + slider_width;
                position.bottom = position.top + slider_height;
            }
            else if (stage == Stage::Default && CheckCursorInSlider(msg.x, msg.y))
                stage = Stage::Hovered;
            else if (stage == Stage::Hovered && !CheckCursorInSlider(msg.x, msg.y))
                stage = Stage::Default;
            break;
        case WM_LBUTTONDOWN:
            if (stage == Stage::Hovered)
            {
                stage = Stage::Pushed;
                cur_x = msg.x;
                cur_y = msg.y;
            }
            break;
        case WM_LBUTTONUP:
            if (stage == Stage::Pushed)
                stage = Stage::Hovered;
            break;
        default:
            break;
    }
}
//virtual void OnClick() = 0;//在子类按钮按下时重写逻辑
void Slider::OnClick(){return;};
bool Slider::CheckCursorInSlider(int x, int y)
{
    return position.left <= x && x <= position.right && position.top <= y && y <= position.bottom;
}
