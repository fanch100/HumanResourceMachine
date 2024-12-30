#include "main.hpp"



QuitButton::QuitButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
QuitButton::~QuitButton() = default;
void QuitButton::OnClick()
{
    is_game_quited = true;
}
